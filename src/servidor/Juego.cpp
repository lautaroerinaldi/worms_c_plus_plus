/*
 * Juego.cpp
 */

#include "Juego.h"

#include <exception>
#include <iostream>

#include "../comun/Buzon.h"
#include "../comun/Codigos.h"
#include "../comun/DefinicionesPrivadas.h"
#include "../comun/Protocolo/ControlMaquinaDeEstados/FinalizarEscenario.h"
#include "../comun/Protocolo/ControlMaquinaDeEstados/FinalizarPartida.h"
#include "../comun/Protocolo/ControlMaquinaDeEstados/IniciarPartida.h"
#include "../comun/Protocolo/NotificarGanador.h"
#include "../comun/Protocolo/Turnos/FinalizarTurno.h"
#include "../comun/Protocolo/Turnos/IniciarTurno.h"
#include "../comun/Protocolo/Turnos/TiempoRestante.h"
#include "../comun/Utiles/Tiempo.h"
#include "../parsers/ParserEscenario.h"

Juego::Juego(Correo & correo, int cantidad_jugadores_esperados,
		std::string nombre_escenario) :
		en_juego(false), cantidad_jugadores_esperados(
				cantidad_jugadores_esperados), cantidad_jugadores_activos(0), correo(
				correo), modelo(cantidad_jugadores_esperados,
				correo.getBuzonSalida()), procesador_entradas(modelo,
				correo.getBuzonSalida()), nombre_escenario(nombre_escenario) {
}

bool Juego::hayMensajesRecibidosSinLeer() {
	return correo.getBuzonEntrada().hayMensajes();
}

void Juego::procesarEntradasPartidaIniciada() {
	while ((en_juego) && hayMensajesRecibidosSinLeer()) {
		Mensaje mensaje(correo.getBuzonEntrada().obtenerMensaje());
		procesador_entradas.procesarPartidaEnJuego(mensaje.getMensaje());
	}
}

bool Juego::hayJugadoresActivos() {
	return (this->getCantidadJugadoresActivos() > 0);
}

void Juego::controlarTurnos() {
	if (modelo.obtenerEstadoDeTurno() == TERMINADO) {
		correo.getBuzonSalida().agregarMensaje(FinalizarTurno());
		modelo.iniciarTurno();
		if (modelo.obtenerEstadoDeTurno() == EN_TURNO) {
			correo.getBuzonSalida().agregarMensaje(
					IniciarTurno(modelo.obtenerIDJugadorEnTurno(),
							modelo.obtenerIDGusanoEnTurno()));
		} else {
			if (modelo.obtenerEstadoDeTurno() == SIN_TURNO) {
				if (hayJugadoresActivos())
					correo.getBuzonSalida().agregarMensaje(FinalizarPartida());
				this->terminar();
			}
		}

	}
}

void Juego::controlarGanadores() {
	int jugador_ganador = modelo.buscarGanador();
	if (jugador_ganador != 0) {
		correo.getBuzonSalida().agregarMensaje(
				NotificarGanador(jugador_ganador));
		this->terminar();
	}
}

void Juego::prepararPartida() {
	correo.getBuzonSalida().agregarMensaje(FinalizarEscenario());
	correo.getBuzonSalida().agregarMensaje(
			IniciarTurno(ID_JUGADOR_MINIMO, ID_GUSANO_MINIMO));

	correo.getBuzonSalida().agregarMensaje(IniciarPartida());
}

void Juego::cargarEscenario() {
	ParserEscenario pe;
	pe.levantarEscenario(this->modelo, nombre_escenario);
}

void Juego::run() {
	try {
		en_juego = true;
		cargarEscenario();
		prepararPartida();
		modelo.inicioPartida();
		while ((en_juego) && (hayJugadoresActivos())) {
			Tiempo tiempo(TIEMPO_ESPERA_EN_MICROSEGUNDOS);
			procesarEntradasPartidaIniciada();
			int tiempo_turno_restante = modelo.actualizar();
			correo.getBuzonSalida().agregarMensaje(
					TiempoRestante(tiempo_turno_restante));
			controlarTurnos();
			controlarGanadores();
		}
	} catch (const std::exception & e) {
		std::cerr << e.what() << std::endl;
		std::flush(std::cerr);
	}
}

unsigned int Juego::getCantidadJugadoresActivos() const {
	return cantidad_jugadores_activos;
}

void Juego::setCantidadJugadoresActivos(unsigned int cantidadJugadoresActivos) {
	cantidad_jugadores_activos = cantidadJugadoresActivos;
}

void Juego::terminar() {
	this->en_juego = false;
}

void Juego::eliminarJugador(int id_jugador) {
	modelo.eliminarJugador(id_jugador);
}

Juego::~Juego() {
}

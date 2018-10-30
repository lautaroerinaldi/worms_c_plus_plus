/*
 * Cliente.cpp
 */

#include "Cliente.h"

#include <unistd.h>
#include <iostream>

#include "../comun/Protocolo/ControlPartidas/CrearPartida.h"
#include "../comun/Protocolo/ControlPartidas/UnirseAPartida.h"
#include "../comun/Protocolo/Protocolo.h"

#include "../comun/Protocolo/NotificarIdPartida.h"
#include "../comun/Protocolo/NotificarIdJugador.h"

Cliente::Cliente() :
		partida(this), sdl_juego(this), procesador(partida, sdl_juego), activo(
				true), cartero(buzon, protocolo), estado_partida(creando) {
}

int Cliente::conectarseAlServer(const std::string & ip,
		const std::string & puerto) {
	return protocolo.conectarseAlServer(ip, puerto);
}

void Cliente::procesarPerdidaDeConexionConServidor() {
	partida.mostrarMje(
			"Se perdió la conexión con el servidor. Cerrando cliente...");
	partida.finalizarPartida();
	apagar();
}

void Cliente::procesarCargaEscenario() {
	std::string mensaje(buzon.obtenerMensaje());
	if (mensaje == SALIR)
		this->procesarPerdidaDeConexionConServidor();
	else
		procesador.procesarCargarEscenario(mensaje, estado_partida);
}

void Cliente::cargarEscenario() {
	while ((this->activo) && (estado_partida == cargando_escenario)) {
		cartero.esperarMensaje();
		procesarCargaEscenario();
	}
}

void Cliente::procesarPartidaEnJuego() {
	if (buzon.hayMensajes()) {
		std::string mensaje(buzon.obtenerMensaje());
		if (mensaje == SALIR)
			this->procesarPerdidaDeConexionConServidor();
		else
			procesador.procesarPartidaEnJuego(mensaje, this);
	}
}

void Cliente::jugarPartida() {
	while ((this->activo) && (estado_partida == en_curso)) {
		cartero.esperarMensaje();
		procesarPartidaEnJuego();
	}
}

void Cliente::procesarLogueo() {
	if (buzon.hayMensajes()) {
		std::string mensaje(buzon.obtenerMensaje());
		if (mensaje == SALIR)
			this->procesarPerdidaDeConexionConServidor();
		else
			procesador.procesarLogueo(mensaje, estado_partida, this);
	}
}

void Cliente::loguearseEnPartida() {
	this->sdl_juego.start();
	while ((this->activo) && (estado_partida == creando)) {
		cartero.esperarMensaje();
		procesarLogueo();
	}
	this->sdl_juego.cerrarPantallasIniciales();
	this->sdl_juego.join();
}

void Cliente::iniciar() {
	loguearseEnPartida();
	cargarEscenario();

	if (estado_partida == en_curso) {
		this->partida.start();
		jugarPartida();
		this->partida.join();
	}
}

void Cliente::enviarMensaje(const Mensaje& mensaje) {
	if ((estado_partida == en_curso) && (id_jugador != id_jugador_activo))
		partida.mostrarMje("No es tu turno.");
	else
		protocolo.enviarMensaje(mensaje.serializar());
}

void Cliente::apagar() {
	if (activo) {
		estado_partida = finalizada;
		activo = false;
		protocolo.desconectarseDelServer();
	}
}

std::string Cliente::recibirMensaje() {
	return protocolo.recibirMensaje();
}

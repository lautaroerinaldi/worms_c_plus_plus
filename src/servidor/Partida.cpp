/*
 * Partida.cpp
 */

#include "Partida.h"
#include "../comun/DefinicionesPrivadas.h"
#include "../comun/Protocolo/Protocolo.h"
#include "../comun/Utiles/Excepcion.h"

#include <sstream>
#include <string>
#include <algorithm>

int Partida::cantidad_partidas_creadas = 0;

Partida::Partida(unsigned int cantidad_jugadores_esperados, int id_escenario,
		const std::string & nombre_escenario) :
		id(++Partida::cantidad_partidas_creadas), cantidad_jugadores_esperados(
				cantidad_jugadores_esperados), fue_iniciada_alguna_vez(false), id_escenario(
				id_escenario), nombre_escenario(nombre_escenario), correo(
				clientes), juego(correo, cantidad_jugadores_esperados,
				nombre_escenario) {
}

unsigned int Partida::getId() const {
	return id;
}

bool Partida::fueIniciadaAlgunaVez() const {
	return fue_iniciada_alguna_vez;
}

unsigned int Partida::getCantidadJugadoresEsperados() const {
	return cantidad_jugadores_esperados;
}

unsigned int Partida::getCantidadJugadoresUnidos() const {
	return clientes.size();
}

bool Partida::hayJugadoresMinimos() {
	if (getCantidadJugadoresUnidos() >= getCantidadJugadoresEsperados())
		return true;
	return false;
}

std::string Partida::serializar() {
	std::ostringstream partida_serializada;
	partida_serializada << getId() << DELIMITADOR_CAMPOS
			<< getCantidadJugadoresUnidos() << DELIMITADOR_CAMPOS
			<< getCantidadJugadoresEsperados() << DELIMITADOR_CAMPOS
			<< id_escenario << DELIMITADOR_CAMPOS << nombre_escenario;
	return partida_serializada.str();
}

bool Partida::contieneACliente(unsigned int id_cliente) {
	std::list<ManejadorDeCliente*>::iterator it = clientes.begin();
	while (it != clientes.end()) {
		if ((*it)->getId() == id_cliente)
			return true;
		++it;
	}
	return false;
}

void Partida::removerCliente(ManejadorDeCliente & cliente) {
	clientes.remove(&cliente);
	if (fue_iniciada_alguna_vez) {
		juego.eliminarJugador(cliente.getIdJugador());
		juego.setCantidadJugadoresActivos(clientes.size());
	}
}

void Partida::agregarCliente(ManejadorDeCliente & cliente)
		throw (std::exception) {
	if (!this->fueIniciadaAlgunaVez()) {
		clientes.push_back(&cliente);
		juego.setCantidadJugadoresActivos(clientes.size());

		if (this->hayJugadoresMinimos())
			this->iniciarPartida();
	} else {
		throw Excepcion(
				"No se pueden unir clientes a una partida ya iniciada.");
	}
}

void Partida::iniciarTodosLosClientes() {
	int id_a_asignar = ID_JUGADOR_MINIMO;
	for (std::list<ManejadorDeCliente*>::iterator it = clientes.begin();
			it != clientes.end(); ++it, ++id_a_asignar) {
		(*it)->iniciarPartidaYNotificarIdJugador(
				&this->correo.getBuzonEntrada(), id_a_asignar);
	}
}

void Partida::iniciarPartida() {
	this->iniciarTodosLosClientes();
	juego.setCantidadJugadoresActivos(clientes.size());
	fue_iniciada_alguna_vez = true;
	juego.start();
}

void Partida::finalizarPartida() {
	juego.terminar();
	juego.join();
}

Partida::~Partida() {
}

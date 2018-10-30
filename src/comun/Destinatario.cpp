/*
 * Destinatario.cpp
 */

#include "Destinatario.h"

#include "DefinicionesPrivadas.h"

Destinatario::Destinatario() :
		id_jugador(ID_JUGADOR_INVALIDO), id_jugador_activo(ID_JUGADOR_INVALIDO) {
}

Destinatario::~Destinatario() {
}

int Destinatario::getIdJugador() const {
	return id_jugador;
}

int Destinatario::getIdJugadorActivo() const {
	return id_jugador_activo;
}

void Destinatario::setIdJugadorActivo(int id_jugador_activo) {
	this->id_jugador_activo = id_jugador_activo;
}

void Destinatario::setIdJugador(int id_jugador) {
	this->id_jugador = id_jugador;
}

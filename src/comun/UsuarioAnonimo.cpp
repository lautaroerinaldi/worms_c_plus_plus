/*
 * UsuarioAnonimo.cpp
 */

#include "UsuarioAnonimo.h"

#include <iostream>

#include "Protocolo/ControlPartidas/SolicitarEscenarios.h"
#include "Protocolo/ControlPartidas/SolicitarPartidasNoIniciadas.h"

UsuarioAnonimo::UsuarioAnonimo() {
}

void UsuarioAnonimo::crearYUnirseAPartida(const CrearPartida & cp) {
	this->enviarMensaje(cp);
}

void UsuarioAnonimo::unirseAPartida(const UnirseAPartida & up) {
	this->enviarMensaje(up);
}

void UsuarioAnonimo::listarPartidasNoIniciadas() {
	SolicitarPartidasNoIniciadas lpni;
	this->enviarMensaje(lpni);
}

void UsuarioAnonimo::listarEscenarios() {
	SolicitarEscenarios le;
	this->enviarMensaje(le);
}

UsuarioAnonimo::~UsuarioAnonimo() {
}

/*
 * SolicitarSaltar.cpp
 */

#include "SolicitarSaltar.h"

#include "../Protocolo.h"

std::string SolicitarSaltar::getComando() const {
	return SOLICITAR_SALTAR;
}

SolicitarSaltar::SolicitarSaltar(const std::string & comando_completo)
		throw (std::exception) :
		SolicitarMover(comando_completo) {
}

SolicitarSaltar::SolicitarSaltar(int direccion)
		throw (std::exception) :
		SolicitarMover(direccion) {
}

SolicitarSaltar::~SolicitarSaltar() {
}

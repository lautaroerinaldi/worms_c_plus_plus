/*
 * SolicitarRetroceso.cpp
 */

#include "SolicitarRetroceso.h"

#include "../Protocolo.h"

std::string SolicitarRetroceso::getComando() const {
	return SOLICITAR_RETROCESO;
}

SolicitarRetroceso::SolicitarRetroceso(const std::string & comando_completo)
		throw (std::exception) :
		SolicitarMover(comando_completo) {
}

SolicitarRetroceso::SolicitarRetroceso(int direccion)
		throw (std::exception) :
		SolicitarMover(direccion) {
}

SolicitarRetroceso::~SolicitarRetroceso() {
}

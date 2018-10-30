/*
 * CarteroReceptorDelCliente.cpp
 */

#include "CarteroReceptorDelCliente.h"

#include <exception>
#include <iostream>

#include "../comun/Protocolo/Protocolo.h"
#include "ProtocoloComunicacionConServer.h"

CarteroReceptorDelCliente::CarteroReceptorDelCliente(Buzon<std::string> & buzon,
		ProtocoloComunicacionConServer & protocolo) :
		buzon(buzon), protocolo(protocolo) {
}

void CarteroReceptorDelCliente::esperarMensaje() {
	try {
		std::string mensaje = protocolo.recibirMensaje();
		buzon.agregarMensaje(mensaje);
	} catch (std::exception & e) {
		std::cerr << e.what() << std::endl;
		buzon.agregarMensaje(SALIR);
	}
}

CarteroReceptorDelCliente::~CarteroReceptorDelCliente() {
}

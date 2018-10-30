/*
 * ProtocoloComunicacionConCliente.cpp
 */

#include "ProtocoloComunicacionConCliente.h"

#include "../comun/Protocolo/Protocolo.h"

ProtocoloComunicacionConCliente::ProtocoloComunicacionConCliente(
		SocketComunicador canal) :
		canal(std::move(canal)) {
}

void ProtocoloComunicacionConCliente::enviarMensaje(
		const std::string& mensaje) {
	canal.enviarDatos(mensaje);
}

std::string ProtocoloComunicacionConCliente::recibirMensaje() {
	std::string mensaje = canal.recibirDatos(DELIMITADOR_REGISTROS);
	return mensaje;
}

void ProtocoloComunicacionConCliente::cerrarConexion() {
	canal.cerrarSocket();
}

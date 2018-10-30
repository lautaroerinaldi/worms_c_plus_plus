/*
 * ProtocoloComunicacionConServer.cpp
 */

#include "ProtocoloComunicacionConServer.h"

#include <sstream>

#include "../comun/Protocolo/Protocolo.h"
#include "../comun/Sockets/SocketComunicador.h"

ProtocoloComunicacionConServer::ProtocoloComunicacionConServer() :
		canal(NULL) {
}

int ProtocoloComunicacionConServer::conectarseAlServer(const std::string & ip,
		const std::string & puerto) {
	canal = new SocketComunicador(ip, puerto);
	if (canal->conexionValida())
		return true;
	else
		return false;
}

void ProtocoloComunicacionConServer::desconectarseDelServer() {
	std::ostringstream mensaje("");
	mensaje << SALIR << DELIMITADOR_REGISTROS;
	this->enviarMensaje(mensaje.str());

	canal->cerrarSocket();
	if (canal)
		delete canal;
}

std::string ProtocoloComunicacionConServer::getPartidas() {
	std::ostringstream mensaje("");
	mensaje << SOLICITAR_TODAS_LAS_PARTIDAS << DELIMITADOR_REGISTROS;
	this->enviarMensaje(mensaje.str());
	return (this->recibirMensaje());
}

std::string ProtocoloComunicacionConServer::getEscenarios() {
	std::ostringstream mensaje("");
	mensaje << SOLICITAR_ESCENARIOS << DELIMITADOR_REGISTROS;
	this->enviarMensaje(mensaje.str());
	return (this->recibirMensaje());
}

std::string ProtocoloComunicacionConServer::recibirMensaje() {
	std::string mensaje = canal->recibirDatos(DELIMITADOR_REGISTROS);
	return mensaje;
}

void ProtocoloComunicacionConServer::enviarMensaje(
		const std::string & mensaje) {
	canal->enviarDatos(mensaje);
}

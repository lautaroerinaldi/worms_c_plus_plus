/*
 * ProtocoloComunicacionConServer.h
 */

#ifndef SRC_CLIENTE_PROTOCOLOCOMUNICACIONCONSERVER_H_
#define SRC_CLIENTE_PROTOCOLOCOMUNICACIONCONSERVER_H_

#include <string>

class SocketComunicador;

class ProtocoloComunicacionConServer {
	SocketComunicador * canal;

public:
	ProtocoloComunicacionConServer();

	int conectarseAlServer(const std::string & ip, const std::string & puerto);

	void desconectarseDelServer();

	std::string getPartidas();

	std::string getEscenarios();

	std::string recibirMensaje();

	void enviarMensaje(const std::string & mensaje);
};

#endif /* SRC_CLIENTE_PROTOCOLOCOMUNICACIONCONSERVER_H_ */

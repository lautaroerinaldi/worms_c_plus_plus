/*
 * ProtocoloComunicacionConCliente.h
 */

#ifndef SERVIDOR_SERVER_PROTOCOLOCOMUNICACIONCONCLIENTE_H_
#define SERVIDOR_SERVER_PROTOCOLOCOMUNICACIONCONCLIENTE_H_

#include <string>

#include "../comun/Sockets/SocketComunicador.h"

class ProtocoloComunicacionConCliente {
	SocketComunicador canal;
public:
	explicit ProtocoloComunicacionConCliente(SocketComunicador canal);

	void enviarMensaje(const std::string & mensaje);

	std::string recibirMensaje();

	void cerrarConexion();

	// COPIAR ProtocoloComunicacionConCliente
	ProtocoloComunicacionConCliente(const ProtocoloComunicacionConCliente& otro) = delete;
	ProtocoloComunicacionConCliente& operator=(
			const ProtocoloComunicacionConCliente& otro) = delete;

	// MOVER ProtocoloComunicacionConCliente
	ProtocoloComunicacionConCliente(ProtocoloComunicacionConCliente&& otro) = delete;
	ProtocoloComunicacionConCliente& operator=(
			ProtocoloComunicacionConCliente&& otro) = delete;
};

#endif /* SERVIDOR_SERVER_PROTOCOLOCOMUNICACIONCONCLIENTE_H_ */

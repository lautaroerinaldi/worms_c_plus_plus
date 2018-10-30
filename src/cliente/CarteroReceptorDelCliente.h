/*
 * CarteroReceptorDelCliente.h
 */

#ifndef CARTERO_RECEPTOR_DEL_CLIENTE_H_
#define CARTERO_RECEPTOR_DEL_CLIENTE_H_

#include <string>

#include "../comun/Buzon.h"

class ProtocoloComunicacionConServer;

class CarteroReceptorDelCliente {
	Buzon<std::string> & buzon;
	ProtocoloComunicacionConServer & protocolo;

public:
	CarteroReceptorDelCliente(Buzon<std::string> & buzon,
			ProtocoloComunicacionConServer & protocolo);

	void esperarMensaje();

	virtual ~CarteroReceptorDelCliente();
};

#endif /* CARTERO_RECEPTOR_DEL_CLIENTE_H_ */

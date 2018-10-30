/*
 * CarteroEmisorDelServer.h
 */

#ifndef SRC_SERVIDOR_CARTEROEMISORDELSERVER_H_
#define SRC_SERVIDOR_CARTEROEMISORDELSERVER_H_

#include <list>

#include "../comun/Buzon.h"
#include "../comun/Protocolo/Mensaje.h"
#include "ManejadorDeCliente.h"

class CarteroEmisorDelServer: public Thread {
	bool activo;
	Buzon<Mensaje> & buzon;
	std::list<ManejadorDeCliente*> & destinatarios;

	void activar();

	void notificarATodos(Mensaje & mensaje);

	void notificarAEmisor(int id_emisor, Mensaje & mensaje);

protected:

	void run();

public:
	CarteroEmisorDelServer(Buzon<Mensaje> & buzon,
			std::list<ManejadorDeCliente*> & destinatarios);

	virtual ~CarteroEmisorDelServer();

	void detener();

	bool estaActivo();

	// COPIAR CarteroEmisorDelServer
	CarteroEmisorDelServer(const CarteroEmisorDelServer& otro) = delete;
	CarteroEmisorDelServer& operator=(
			const CarteroEmisorDelServer& otro) = delete;

	// MOVER CarteroEmisorDelServer
	CarteroEmisorDelServer(CarteroEmisorDelServer&& otro) = delete;
	CarteroEmisorDelServer& operator=(
			CarteroEmisorDelServer&& otro) = delete;
};

#endif /* SRC_SERVIDOR_CARTEROEMISORDELSERVER_H_ */

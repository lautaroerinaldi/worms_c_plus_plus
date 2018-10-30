/*
 * Server.h
 */

#ifndef SERVIDOR_SERVER_SERVIDOR_H_
#define SERVIDOR_SERVER_SERVIDOR_H_

#include "AdministradorDePartidas.h"
#include "ManejadorDeCliente.h"

#include "../comun/Sockets/SocketAceptador.h"
#include "../comun/Threads/Thread.h"

#include <list>

class Servidor: public Thread {
	SocketAceptador skt_server;
	bool vivo;
	std::list<ManejadorDeCliente> clientes;
	AdministradorDePartidas & admin_partidas;

	void aceptarNuevoCliente();

	/**
	 * Recorre la lista de manejadores de clientes y luego libera los recursos
	 * y borra de la lista a todos los clientes que no están activos (es decir,
	 * los que se joinearon solos porque ya terminaron su tarea)
	 */
	void recolectarClientesMuertos();

	void apagarClientesVivos();

	static bool clienteMuerto(const ManejadorDeCliente & cliente);

	static void joinearClienteMuerto(ManejadorDeCliente & cliente);

	static void apagarClienteVivo(ManejadorDeCliente & cliente);


protected:
	/**
	 * Inicia en un nuevo hilo y desde acá va aceptando los nuevos clientes.
	 */
	void run();

public:
	explicit Servidor(const std::string & puerto);

	/**
	 * Cierra el socket aceptador y a partir de ese momento no se pueden
	 * aceptar más conexiones entrantes. Luego recolecta todos los clientes
	 */
	void apagar();

	/**
	 * libera los recursos utilizados por el server
	 */
	virtual ~Servidor();

	// COPIAR Server
	Servidor(const Servidor& otro) = delete;
	Servidor& operator=(const Servidor& otro) = delete;

	// MOVER Server
	Servidor(Servidor && otro) = delete;
	Servidor& operator=(Servidor&& otro) = delete;
};

#endif /* SERVIDOR_SERVER_SERVIDOR_H_ */

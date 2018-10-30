/*
 * ManejadorDeCliente.h
 */

#ifndef SERVIDOR_SERVER_MANEJADORDECLIENTE_H_
#define SERVIDOR_SERVER_MANEJADORDECLIENTE_H_

#include "ProtocoloComunicacionConCliente.h"
#include "../comun/Destinatario.h"
#include <string>

#include "../comun/Sockets/SocketComunicador.h"
#include "../comun/Threads/Thread.h"
#include "../comun/Buzon.h"
#include "../comun/Protocolo/Mensaje.h"

class ManejadorDeCliente: public Thread, public Destinatario {
	static int cantidad_clientes_creados;

	unsigned int id;
	ProtocoloComunicacionConCliente protocolo;
	bool activo;
	Buzon<Mensaje> * buzon;

	typedef enum {
		partida_no_iniciada,
		esperando_iniciar_partida,
		partida_en_curso,
		partida_finalizada
	} estados_posibles_T;

	estados_posibles_T estado_partida;

	void manejarPartidaNoIniciada();

	void manejarPartida();

	bool partidaNoIniciada();

	void finalizarPartida();

	// Heredado de Destinatario
	void enviarMensaje(const Mensaje & mensaje);

protected:
	/**
	 * Inicia en un nuevo hilo y .....
	 */
	void run();

public:
	/**
	 * El cliente se inicia solo en un nuevo hilo.
	 */
	explicit ManejadorDeCliente(SocketComunicador canal);

	unsigned int getId() const;

	bool isActivo() const;

	void iniciarPartidaYNotificarIdJugador(Buzon<Mensaje> * buzon, int id_jugador);

	void enviarMensaje(const std::string& mensaje);

	void apagar();

	~ManejadorDeCliente();

	// COPIAR ManejadorDeCliente
	ManejadorDeCliente(const ManejadorDeCliente& otro) = delete;
	ManejadorDeCliente& operator=(const ManejadorDeCliente& otro) = delete;

	// MOVER ManejadorDeCliente
	ManejadorDeCliente(ManejadorDeCliente && otro) = delete;
	ManejadorDeCliente& operator=(ManejadorDeCliente&& otro) = delete;
};

#endif /* SERVIDOR_SERVER_MANEJADORDECLIENTE_H_ */

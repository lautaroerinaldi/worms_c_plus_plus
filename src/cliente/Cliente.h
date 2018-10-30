/*
 * Cliente.h
 */

#ifndef CLIENTE_CLIENTE_H_
#define CLIENTE_CLIENTE_H_

#include <string>

#include "../comun/Buzon.h"
#include "../comun/DefinicionesPrivadas.h"
#include "../comun/Destinatario.h"
#include "../comun/UsuarioAnonimo.h"
#include "../vista/elementos/SdlPartida.h"
#include "CarteroReceptorDelCliente.h"
#include "ProcesadorDeEntradas.h"
#include "ProtocoloComunicacionConServer.h"
#include "../vista/elementos/SdlJuego.h"

class Cliente: public Destinatario, public UsuarioAnonimo {
	Buzon<std::string> buzon;
	SdlPartida partida;
	SdlJuego sdl_juego;
	ProcesadorDeEntradas procesador;
	bool activo;

	ProtocoloComunicacionConServer protocolo;
	CarteroReceptorDelCliente cartero;
	estados_posibles_partida estado_partida;

	std::string recibirMensaje();
	void enviarMensaje(const Mensaje & mensaje);

	void procesarPerdidaDeConexionConServidor();

	void cargarEscenario();
	void procesarCargaEscenario();

	void procesarPartidaEnJuego();
	void jugarPartida();

	void procesarLogueo();
	void loguearseEnPartida();

public:
	Cliente();

	int conectarseAlServer(const std::string & ip, const std::string & puerto);

	void iniciar();

	void apagar();

	// COPIAR Cliente
	Cliente(const Cliente& otro) = delete;
	Cliente& operator=(const Cliente& otro) = delete;

	// MOVER Cliente
	Cliente(Cliente&& otro) = delete;
	Cliente& operator=(Cliente&& otro) = delete;
};

#endif /* CLIENTE_CLIENTE_H_ */

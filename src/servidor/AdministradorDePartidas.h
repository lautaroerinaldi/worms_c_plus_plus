/*
 * AdministradorDePartidas.h
 */

#ifndef SERVIDOR_SERVER_ADMINISTRADORDEPARTIDAS_H_
#define SERVIDOR_SERVER_ADMINISTRADORDEPARTIDAS_H_

#include <list>
#include <string>

#include "../comun/Protocolo/ControlPartidas/CrearPartida.h"
#include "../comun/Protocolo/ControlPartidas/UnirseAPartida.h"
#include "../comun/Threads/Mutex.h"
#include "Partida.h"

class AdministradorDePartidas {
	Mutex mutex;

	std::list<Partida> partidas;

	explicit AdministradorDePartidas();

	Partida * localizarPartida(const unsigned int id) throw (std::exception);

	std::string localizarNombreEscenario(int id_escenario);

public:

	Partida* clienteEstaEnAlgunaPartida(ManejadorDeCliente & cliente);

	static AdministradorDePartidas &getInstancia();

	int crearPartida(const CrearPartida & partida_a_crear)
			throw (std::exception);

	void unirseAPartida(const UnirseAPartida & partida_a_unirse,
			ManejadorDeCliente & cliente) throw (std::exception);

	void salirDePartida(ManejadorDeCliente & cliente);

	std::string listarPartidas() throw (std::exception);

	std::string listarPartidasNoIniciadas() throw (std::exception);

	void cerrarTodasLasPartidas();

	~AdministradorDePartidas();

	// COPIAR 	AdministradorDePartidas
	AdministradorDePartidas(const AdministradorDePartidas& otro) = delete;
	AdministradorDePartidas& operator=(const AdministradorDePartidas& otro) = delete;

	// MOVER 	AdministradorDePartidas
	AdministradorDePartidas(AdministradorDePartidas&& otro) = delete;
	AdministradorDePartidas& operator=(AdministradorDePartidas&& otro) = delete;
};

#endif /* SERVIDOR_SERVER_ADMINISTRADORDEPARTIDAS_H_ */

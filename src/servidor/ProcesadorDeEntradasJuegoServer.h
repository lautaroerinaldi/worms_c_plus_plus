/*
 * ProcesadorDeEntradasJuegoServer.h
 */

#ifndef SRC_SERVIDOR_PROCESADORDEENTRADASJUEGOSERVER_H_
#define SRC_SERVIDOR_PROCESADORDEENTRADASJUEGOSERVER_H_

#include "../comun/Protocolo/Mensaje.h"
#include "../comun/Buzon.h"
#include "../comun/DefinicionesPrivadas.h"
#include "../modelo/Modelo.h"

#include <map>
#include <string>

class ProcesadorDeEntradasJuegoServer {
	Modelo & modelo;
	Buzon<Mensaje> & buzon_salida;
	std::map<std::string, comandos_partida_posibles> comandos;

	void inicializarComandosPartida();

public:
	ProcesadorDeEntradasJuegoServer(Modelo & modelo,
			Buzon<Mensaje> & buzon_salida);

	void procesarPartidaEnJuego(const std::string & mensaje);

	// COPIAR ProcesadorDeEntradasJuegoServer
	ProcesadorDeEntradasJuegoServer(const ProcesadorDeEntradasJuegoServer& otro) = delete;
	ProcesadorDeEntradasJuegoServer& operator=(
			const ProcesadorDeEntradasJuegoServer& otro) = delete;

	// MOVER ProcesadorDeEntradasJuegoServer
	ProcesadorDeEntradasJuegoServer(ProcesadorDeEntradasJuegoServer&& otro) = delete;
	ProcesadorDeEntradasJuegoServer& operator=(
			ProcesadorDeEntradasJuegoServer&& otro) = delete;

	~ProcesadorDeEntradasJuegoServer();
};

#endif /* SRC_SERVIDOR_PROCESADORDEENTRADASJUEGOSERVER_H_ */

/*
 * ProcesadorDeEntradas.h
 */

#ifndef SRC_CLIENTE_PROCESADORDEENTRADAS_H_
#define SRC_CLIENTE_PROCESADORDEENTRADAS_H_

#include <map>
#include <string>
#include "../vista/elementos/SdlPartida.h"
#include "../comun/DefinicionesPrivadas.h"
#include "../comun/Destinatario.h"
#include "../vista/elementos/SdlJuego.h"

class ProcesadorDeEntradas {
	SdlPartida & partida;
	SdlJuego & sdl_juego;

	std::map<std::string, int> comandos_escenario;

	std::map<std::string, int> comandos_partida;

	std::map<std::string, int> respuestas_logueo;

	void inicializarComandosEscenario();

	void inicializarComandosPartida();

	void inicializarComandosRespuestasLogueo();

	void procesarComandoInvalido(const std::string& mensaje);

	void procesarExcepcion(std::exception& e);

public:
	ProcesadorDeEntradas(SdlPartida & partida, SdlJuego & sdl_juego);

	void procesarLogueo(const std::string mensaje,
			estados_posibles_partida & estado_partida,
			Destinatario * destinatario);

	void procesarCargarEscenario(const std::string mensaje,
			estados_posibles_partida & estado_partida);

	void procesarPartidaEnJuego(const std::string mensaje,
			Destinatario * destinatario);

	~ProcesadorDeEntradas();

	// COPIAR ProcesadorDeEntradas
	ProcesadorDeEntradas(const ProcesadorDeEntradas& otro) = delete;
	ProcesadorDeEntradas& operator=(const ProcesadorDeEntradas& otro) = delete;

	// MOVER ProcesadorDeEntradas
	ProcesadorDeEntradas(ProcesadorDeEntradas&& otro) = delete;
	ProcesadorDeEntradas& operator=(ProcesadorDeEntradas&& otro) = delete;
};

#endif /* SRC_CLIENTE_PROCESADORDEENTRADAS_H_ */

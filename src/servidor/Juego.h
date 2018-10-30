/*
 * Juego.h
 */

#ifndef SERVIDOR_SERVER_JUEGO_H_
#define SERVIDOR_SERVER_JUEGO_H_

#include "Correo.h"
#include "../modelo/Modelo.h"
#include "../comun/Threads/Thread.h"
#include "ProcesadorDeEntradasJuegoServer.h"

class Juego: public Thread {
	bool en_juego;
	int cantidad_jugadores_esperados;
	unsigned int cantidad_jugadores_activos;

	Correo & correo;
	Modelo modelo;
	ProcesadorDeEntradasJuegoServer procesador_entradas;

	std::string nombre_escenario;

	void procesarEntradasPartidaIniciada();

	void procesarSalidasPartidaIniciada();

	bool hayJugadoresActivos();

	bool hayMensajesRecibidosSinLeer();

	unsigned int getCantidadJugadoresActivos() const;

	void controlarTurnos();

	void controlarGanadores();

	void prepararPartida();

	void cargarEscenario();

protected:
	void run();

public:
	Juego(Correo & correo, int cantidad_jugadores_esperados, std::string nombre_escenario);

	void setCantidadJugadoresActivos(unsigned int cantidadJugadoresActivos);

	void terminar();

	void eliminarJugador(int id_jugador);

	~Juego();

	// COPIAR Juego
	Juego(const Juego& otro) = delete;
	Juego& operator=(const Juego& otro) = delete;

	// MOVER Juego
	Juego(Juego&& otro) = delete;
	Juego& operator=(Juego&& otro) = delete;
};

#endif /* SERVIDOR_SERVER_JUEGO_H_ */

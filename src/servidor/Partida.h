/**
 * Partida.h
 */

#ifndef SERVIDOR_SERVER_PARTIDA_H_
#define SERVIDOR_SERVER_PARTIDA_H_

#include "Correo.h"
#include "Juego.h"
#include "ManejadorDeCliente.h"

#include <list>
#include <string>

class Partida {
	static int cantidad_partidas_creadas;

	unsigned int id;
	unsigned int cantidad_jugadores_esperados;
	bool fue_iniciada_alguna_vez;

	int id_escenario;
	std::string nombre_escenario;

	std::list<ManejadorDeCliente*> clientes;
	Correo correo;
	Juego juego;

	void iniciarTodosLosClientes();

	void iniciarPartida();

public:
	explicit Partida(unsigned int cantidad_jugadores_esperados,
			int id_escenario, const std::string & nombre_escenario);

	unsigned int getId() const;

	unsigned int getCantidadJugadoresEsperados() const;

	bool fueIniciadaAlgunaVez() const;

	unsigned int getCantidadJugadoresUnidos() const;

	bool hayJugadoresMinimos();

	std::string serializar();

	bool contieneACliente(unsigned int id_cliente);

	void agregarCliente(ManejadorDeCliente & cliente) throw (std::exception);

	void finalizarPartida();

	void removerCliente(ManejadorDeCliente & cliente);

	~Partida();

	// COPIAR Partidas
	Partida(const Partida& otra) = delete;
	Partida& operator=(const Partida& otra) = delete;

	// MOVER Partidas
	Partida(Partida&& otra) = delete;
	Partida& operator=(Partida&& otra) = delete;
};

#endif /* SERVIDOR_SERVER_PARTIDA_H_ */

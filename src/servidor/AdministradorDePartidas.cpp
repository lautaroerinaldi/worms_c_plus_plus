/*
 * AdministradorDePartidas.cpp
 */

#include "AdministradorDePartidas.h"

#include <sstream>

#include "../comun/DefinicionesDePrueba.h"
#include "../comun/DefinicionesPrivadas.h"
#include "../comun/Threads/Lock.h"
#include "../comun/Utiles/Excepcion.h"

#include "Atlas.h"

AdministradorDePartidas::AdministradorDePartidas() {
	Atlas::getInstancia();
}

std::string AdministradorDePartidas::localizarNombreEscenario(
		int id_escenario) {
	return Atlas::getInstancia().getNombreEscenario(id_escenario);
}

Partida * AdministradorDePartidas::clienteEstaEnAlgunaPartida(
		ManejadorDeCliente & cliente) {
	std::list<Partida>::iterator it = partidas.begin();
	for (; it != partidas.end(); ++it)
		if ((it)->contieneACliente(cliente.getId()))
			return &(*it);
	return NULL;
}

Partida* AdministradorDePartidas::localizarPartida(unsigned int id)
		throw (std::exception) {
	std::list<Partida>::iterator it = partidas.begin();
	Partida * partida_encontrada = NULL;
	for (; it != partidas.end(); ++it)
		if ((it)->getId() == id)
			partida_encontrada = &(*it);
	if (partida_encontrada)
		return partida_encontrada;
	else
		throw Excepcion("No existe la partida solicitada.");
}

AdministradorDePartidas & AdministradorDePartidas::getInstancia() {
	static AdministradorDePartidas administrador_de_partidas;
	return administrador_de_partidas;
}

int AdministradorDePartidas::crearPartida(const CrearPartida & partida_a_crear)
		throw (std::exception) {
	Lock lock(this->mutex);
	if ((partida_a_crear.getCantidadJugadoresEsperados()
			>= CANTIDAD_MINIMA_DE_JUGADORES_PERMITIDA)
			&& (partida_a_crear.getIdEscenario()
					<= Atlas::getInstancia().getCantidadEscenarios())) {
		partidas.emplace_back(partida_a_crear.getCantidadJugadoresEsperados(),
				partida_a_crear.getIdEscenario(),
				localizarNombreEscenario(partida_a_crear.getIdEscenario()));
		return partidas.back().getId();
	} else {
		throw Excepcion("Partida no pudo ser creada.");
	}
}

void AdministradorDePartidas::unirseAPartida(
		const UnirseAPartida & partida_a_unirse, ManejadorDeCliente & cliente)
				throw (std::exception) {
	Lock lock(this->mutex);
	if (clienteEstaEnAlgunaPartida(cliente)) {
		throw Excepcion(
				"No se puede UNIR A LA PARTIDA. El cliente ya está unido a una partida.");
	} else {
		Partida * partida = localizarPartida(partida_a_unirse.getIdPartida());
		partida->agregarCliente(cliente);
	}
}

std::string AdministradorDePartidas::listarPartidas() throw (std::exception) {
	Lock lock(this->mutex);
	if (partidas.size() > 0) {
		std::ostringstream lista_partidas;
		for (std::list<Partida>::iterator it = partidas.begin();
				it != partidas.end(); ++it)
			lista_partidas << DELIMITADOR_CAMPOS << (it)->serializar();
		lista_partidas << DELIMITADOR_REGISTROS;
		return lista_partidas.str();
	} else {
		throw Excepcion("No hay partidas que listar.");
	}
}

std::string AdministradorDePartidas::listarPartidasNoIniciadas()
		throw (std::exception) {
	Lock lock(this->mutex);
	if (partidas.size() > 0) {
		std::ostringstream lista_partidas;
		for (std::list<Partida>::iterator it = partidas.begin();
				it != partidas.end(); ++it)
			if (!(it)->fueIniciadaAlgunaVez())
				lista_partidas << DELIMITADOR_CAMPOS << (it)->serializar();
		return lista_partidas.str();
	} else {
		throw Excepcion("No hay partidas no iniciadas que listar.");
	}
}

void AdministradorDePartidas::salirDePartida(ManejadorDeCliente& cliente) {
	Lock lock(this->mutex);
	Partida * partida_que_contiene_a_cliente = clienteEstaEnAlgunaPartida(
			cliente);
	if (partida_que_contiene_a_cliente) {
		partida_que_contiene_a_cliente->removerCliente(cliente);
	}
}

void AdministradorDePartidas::cerrarTodasLasPartidas() {
	Lock lock(this->mutex);
	for (std::list<Partida>::iterator it = partidas.begin();
			it != partidas.end(); ++it) {
		(it)->finalizarPartida();
	}
}

AdministradorDePartidas::~AdministradorDePartidas() {
}

/*
 * CrearPartida.cpp
 */

#include "CrearPartida.h"

#include <sstream>

#include "../../Utiles/Excepcion.h"

destinatarios_posibles CrearPartida::destinatarios =
		destinatarios_posibles::servidor;

CrearPartida::CrearPartida(const std::string& comando_completo)
		throw (std::exception) :
		Mensaje(comando_completo, CrearPartida::destinatarios), id_escenario(
		ID_ESCENARIO_INVALIDO), cantidad_jugadores_esperados(
		CANTIDAD_JUGADORES_INVALIDA) {

	std::istringstream mensaje_a_parsear(comando_completo);

	std::string comando;
	mensaje_a_parsear >> comando;
	mensaje_a_parsear >> this->id_escenario;
	mensaje_a_parsear >> this->cantidad_jugadores_esperados;

	if (!cantidadArgumentosRecibidosCorrecta(mensaje_a_parsear))
		throw Excepcion(
				"Cantidad de Argumentos recibidos en Comando CREAR_PARTIDA no válido.");

	if (comando != CREAR_PARTIDA)
		throw Excepcion("Comando CREAR_PARTIDA no válido.");
}

CrearPartida::CrearPartida(unsigned int id_escenario,
		unsigned int cantidad_jugadores_esperados) :
		id_escenario(id_escenario), cantidad_jugadores_esperados(
				cantidad_jugadores_esperados) {

	this->receptor = getDestinatariosSegunTipoMensaje();
	this->mensaje = serializar();
}

std::string CrearPartida::serializar() {
	std::ostringstream crear_partida;
	crear_partida << CREAR_PARTIDA << DELIMITADOR_CAMPOS << getIdEscenario()
			<< DELIMITADOR_CAMPOS << getCantidadJugadoresEsperados()
			<< DELIMITADOR_REGISTROS;
	return crear_partida.str();
}

unsigned int CrearPartida::getCantidadJugadoresEsperados() const {
	return cantidad_jugadores_esperados;
}

unsigned int CrearPartida::getIdEscenario() const {
	return id_escenario;
}

destinatarios_posibles CrearPartida::getDestinatariosSegunTipoMensaje() const {
	return destinatarios;
}

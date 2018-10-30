/*
 * IniciarTurno.cpp
 */

#include "IniciarTurno.h"

#include "../Protocolo.h"
#include "../../Utiles/Excepcion.h"

#include <sstream>

destinatarios_posibles IniciarTurno::destinatarios =
		destinatarios_posibles::todos;

IniciarTurno::IniciarTurno(const std::string & comando_completo)
		throw (std::exception) :
		Mensaje(comando_completo, IniciarTurno::destinatarios) {

	std::istringstream mensaje_a_parsear(comando_completo);

	std::string comando;
	mensaje_a_parsear >> comando;
	mensaje_a_parsear >> this->id_jugador;
	mensaje_a_parsear >> this->id_gusano;

	if (!cantidadArgumentosRecibidosCorrecta(mensaje_a_parsear))
		throw Excepcion(
				"Cantidad de Argumentos recibidos en Comando INICIAR TURNO no válido.");

	if (comando != INICIAR_TURNO)
		throw Excepcion("Comando INICIAR TURNO no válido.");
}

IniciarTurno::IniciarTurno(int id_jugador, int id_gusano) :
		id_jugador(id_jugador), id_gusano(id_gusano) {

	this->receptor = getDestinatariosSegunTipoMensaje();
	this->mensaje = serializar();
}

int IniciarTurno::getIdJugador() const {
	return id_jugador;
}

int IniciarTurno::getIdGusano() const {
	return id_gusano;
}

destinatarios_posibles IniciarTurno::getDestinatariosSegunTipoMensaje() const {
	return destinatarios;
}

std::string IniciarTurno::serializar() const {
	std::ostringstream iniciar_turno("");
	iniciar_turno << INICIAR_TURNO << DELIMITADOR_CAMPOS << getIdJugador()
			<< DELIMITADOR_CAMPOS << getIdGusano() << DELIMITADOR_REGISTROS;
	return iniciar_turno.str();
}

IniciarTurno::~IniciarTurno() {
}

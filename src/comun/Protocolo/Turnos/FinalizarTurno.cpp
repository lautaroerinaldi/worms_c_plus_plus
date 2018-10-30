/*
 * FinalizarTurno.cpp
 */

#include "FinalizarTurno.h"

#include "../Protocolo.h"
#include "../../Utiles/Excepcion.h"

#include <sstream>

destinatarios_posibles FinalizarTurno::destinatarios =
		destinatarios_posibles::todos;

FinalizarTurno::FinalizarTurno(const std::string & comando_completo)
		throw (std::exception) :
		Mensaje(comando_completo, FinalizarTurno::destinatarios) {

	std::istringstream mensaje_a_parsear(comando_completo);

	std::string comando;
	mensaje_a_parsear >> comando;

	if (!cantidadArgumentosRecibidosCorrecta(mensaje_a_parsear))
		throw Excepcion(
				"Cantidad de Argumentos recibidos en Comando FINALIZAR TURNO no válido.");

	if (comando != FINALIZAR_TURNO)
		throw Excepcion("Comando FINALIZAR TURNO no válido.");
}

FinalizarTurno::FinalizarTurno() {
	this->receptor = getDestinatariosSegunTipoMensaje();
	this->mensaje = serializar();
}

destinatarios_posibles FinalizarTurno::getDestinatariosSegunTipoMensaje() const {
	return destinatarios;
}

std::string FinalizarTurno::serializar() const {
	std::ostringstream finalizar_turno("");
	finalizar_turno << FINALIZAR_TURNO << DELIMITADOR_REGISTROS;
	return finalizar_turno.str();
}

FinalizarTurno::~FinalizarTurno() {
}

/*
 * FinalizarEscenario.cpp
 */

#include "FinalizarEscenario.h"

#include "../Protocolo.h"
#include <sstream>
#include "../../Utiles/Excepcion.h"

destinatarios_posibles FinalizarEscenario::destinatarios =
		destinatarios_posibles::todos;

destinatarios_posibles FinalizarEscenario::getDestinatariosSegunTipoMensaje() const {
	return destinatarios;
}

std::string FinalizarEscenario::serializar() {
	std::ostringstream finalizar_escenario;
	finalizar_escenario << FINALIZAR_ESCENARIO << DELIMITADOR_REGISTROS;
	return finalizar_escenario.str();
}

FinalizarEscenario::FinalizarEscenario(const std::string& comando_completo)
		throw (std::exception) :
		Mensaje(comando_completo, FinalizarEscenario::destinatarios) {

	std::istringstream mensaje_a_parsear(comando_completo);

	std::string comando;
	mensaje_a_parsear >> comando;

	if (!cantidadArgumentosRecibidosCorrecta(mensaje_a_parsear))
		throw Excepcion(
				"Cantidad de Argumentos recibidos en Comando FINALIZAR ESCENARIO no válido.");

	if (comando != FINALIZAR_ESCENARIO)
		throw Excepcion("Comando FINALIZAR ESCENARIO no válido.");

	this->receptor = getDestinatariosSegunTipoMensaje();
	this->mensaje = serializar();
}

FinalizarEscenario::FinalizarEscenario() {
	this->receptor = getDestinatariosSegunTipoMensaje();
	this->mensaje = serializar();
}

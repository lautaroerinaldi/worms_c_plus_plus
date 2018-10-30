/*
 * SolicitarEscenarios.cpp
 */

#include "SolicitarEscenarios.h"

#include "../Protocolo.h"
#include <sstream>
#include "../../Utiles/Excepcion.h"

destinatarios_posibles SolicitarEscenarios::destinatarios =
		destinatarios_posibles::servidor;

SolicitarEscenarios::SolicitarEscenarios(const std::string& comando_completo)
		throw (std::exception) :
		Mensaje(comando_completo, SolicitarEscenarios::destinatarios) {

	std::istringstream mensaje_a_parsear(comando_completo);

	std::string comando;
	mensaje_a_parsear >> comando;

	if (!cantidadArgumentosRecibidosCorrecta(mensaje_a_parsear))
		throw Excepcion(
				"Cantidad de Argumentos recibidos en Comando LISTAR ESCENARIOS no válido.");

	if (comando != SOLICITAR_ESCENARIOS)
		throw Excepcion("Comando LISTAR ESCENARIOS no válido.");

	this->receptor = getDestinatariosSegunTipoMensaje();
	this->mensaje = serializar();
}

SolicitarEscenarios::SolicitarEscenarios() {
	this->receptor = getDestinatariosSegunTipoMensaje();
	this->mensaje = serializar();
}

destinatarios_posibles SolicitarEscenarios::getDestinatariosSegunTipoMensaje() const {
	return destinatarios;
}

std::string SolicitarEscenarios::serializar() {
	std::ostringstream listar_escenarios;
	listar_escenarios << SOLICITAR_ESCENARIOS << DELIMITADOR_REGISTROS;
	return listar_escenarios.str();
}

SolicitarEscenarios::~SolicitarEscenarios() {
}


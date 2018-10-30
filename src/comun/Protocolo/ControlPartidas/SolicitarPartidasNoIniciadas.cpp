/*
 * SolicitarPartidasNoIniciadas.cpp
 */

#include "SolicitarPartidasNoIniciadas.h"

#include "../Protocolo.h"
#include <sstream>
#include "../../Utiles/Excepcion.h"

destinatarios_posibles SolicitarPartidasNoIniciadas::destinatarios =
		destinatarios_posibles::servidor;

SolicitarPartidasNoIniciadas::SolicitarPartidasNoIniciadas(
		const std::string& comando_completo) throw (std::exception) :
		Mensaje(comando_completo, SolicitarPartidasNoIniciadas::destinatarios) {

	std::istringstream mensaje_a_parsear(comando_completo);

	std::string comando;
	mensaje_a_parsear >> comando;

	if (!cantidadArgumentosRecibidosCorrecta(mensaje_a_parsear))
		throw Excepcion(
				"Cantidad de Argumentos recibidos en Comando LISTAR PARTIDAS NO INICIADA no válido.");

	if (comando != SOLICITAR_PARTIDAS_NO_INICIADAS)
		throw Excepcion("Comando LISTAR PARTIDAS NO INICIADA no válido.");

	this->receptor = getDestinatariosSegunTipoMensaje();
	this->mensaje = serializar();
}

SolicitarPartidasNoIniciadas::SolicitarPartidasNoIniciadas() {
	this->receptor = getDestinatariosSegunTipoMensaje();
	this->mensaje = serializar();
}

destinatarios_posibles SolicitarPartidasNoIniciadas::getDestinatariosSegunTipoMensaje() const {
	return destinatarios;
}

std::string SolicitarPartidasNoIniciadas::serializar() {
	std::ostringstream listar_partidas_no_iniciadas;
	listar_partidas_no_iniciadas << SOLICITAR_PARTIDAS_NO_INICIADAS
			<< DELIMITADOR_REGISTROS;
	return listar_partidas_no_iniciadas.str();
}

SolicitarPartidasNoIniciadas::~SolicitarPartidasNoIniciadas() {
}

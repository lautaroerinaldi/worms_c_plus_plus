/*
 * FinalizarPartida.cpp
 */

#include "FinalizarPartida.h"

#include "../Protocolo.h"
#include <sstream>
#include "../../Utiles/Excepcion.h"

destinatarios_posibles FinalizarPartida::destinatarios =
		destinatarios_posibles::todos;

destinatarios_posibles FinalizarPartida::getDestinatariosSegunTipoMensaje() const {
	return destinatarios;
}

std::string FinalizarPartida::serializar() {
	std::ostringstream finalizar_partida;
	finalizar_partida << FINALIZAR_PARTIDA << DELIMITADOR_REGISTROS;
	return finalizar_partida.str();
}

FinalizarPartida::FinalizarPartida(const std::string& comando_completo)
		throw (std::exception) :
		Mensaje(comando_completo, FinalizarPartida::destinatarios) {

	std::istringstream mensaje_a_parsear(comando_completo);

	std::string comando;
	mensaje_a_parsear >> comando;

	if (!cantidadArgumentosRecibidosCorrecta(mensaje_a_parsear))
		throw Excepcion(
				"Cantidad de Argumentos recibidos en Comando FINALIZAR PARTIDA no válido.");

	if (comando != FINALIZAR_PARTIDA)
		throw Excepcion("Comando FINALIZAR PARTIDA no válido.");

	this->receptor = getDestinatariosSegunTipoMensaje();
	this->mensaje = serializar();
}

FinalizarPartida::FinalizarPartida() {
	this->receptor = getDestinatariosSegunTipoMensaje();
	this->mensaje = serializar();
}

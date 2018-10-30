/*
 * IniciarPartida.cpp
 */

#include "IniciarPartida.h"

#include "../Protocolo.h"
#include <sstream>
#include "../../Utiles/Excepcion.h"

destinatarios_posibles IniciarPartida::destinatarios =
		destinatarios_posibles::todos;

destinatarios_posibles IniciarPartida::getDestinatariosSegunTipoMensaje() const {
	return destinatarios;
}

std::string IniciarPartida::serializar() {
	std::ostringstream iniciar_partida;
	iniciar_partida << INICIAR_PARTIDA << DELIMITADOR_REGISTROS;
	return iniciar_partida.str();
}

IniciarPartida::IniciarPartida(const std::string& comando_completo)
		throw (std::exception) :
		Mensaje(comando_completo, IniciarPartida::destinatarios) {

	std::istringstream mensaje_a_parsear(comando_completo);

	std::string comando;
	mensaje_a_parsear >> comando;

	if (!cantidadArgumentosRecibidosCorrecta(mensaje_a_parsear))
		throw Excepcion(
				"Cantidad de Argumentos recibidos en Comando INICIAR PARTIDA no válido.");

	if (comando != INICIAR_PARTIDA)
		throw Excepcion("Comando INICIAR PARTIDA no válido.");

	this->receptor = getDestinatariosSegunTipoMensaje();
	this->mensaje = serializar();
}

IniciarPartida::IniciarPartida() {
	this->receptor = getDestinatariosSegunTipoMensaje();
	this->mensaje = serializar();

}

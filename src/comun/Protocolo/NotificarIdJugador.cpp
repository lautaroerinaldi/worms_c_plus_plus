/*
 * NotificarIdJugador.cpp
 */

#include "NotificarIdJugador.h"

#include "Protocolo.h"
#include <sstream>
#include "../Utiles/Excepcion.h"

destinatarios_posibles NotificarIdJugador::destinatarios =
		destinatarios_posibles::no_es_necesario;

NotificarIdJugador::NotificarIdJugador(const std::string & comando_completo) :
		Mensaje(comando_completo, NotificarIdJugador::destinatarios) {
	std::istringstream mensaje_a_parsear(comando_completo);

	std::string comando;
	mensaje_a_parsear >> comando;
	mensaje_a_parsear >> this->id_jugador;

	if (!cantidadArgumentosRecibidosCorrecta(mensaje_a_parsear))
		throw Excepcion(
				"Cantidad de Argumentos recibidos en Comando NOTIFICAR_ID_JUGADOR no válido.");

	if (comando != NOTIFICAR_ID_JUGADOR)
		throw Excepcion("Comando NOTIFICAR_ID_JUGADOR no válido.");

	this->receptor = getDestinatariosSegunTipoMensaje();
	this->mensaje = serializar();

}

NotificarIdJugador::NotificarIdJugador(int id_jugador) :
		id_jugador(id_jugador) {
	this->receptor = getDestinatariosSegunTipoMensaje();
	this->mensaje = serializar();
}

std::string NotificarIdJugador::serializar() const {
	std::ostringstream oss("");
	oss << NOTIFICAR_ID_JUGADOR << DELIMITADOR_CAMPOS << getIdJugador()
			<< DELIMITADOR_REGISTROS;
	return oss.str();
}

destinatarios_posibles NotificarIdJugador::getDestinatariosSegunTipoMensaje() const {
	return destinatarios;
}

int NotificarIdJugador::getIdJugador() const {
	return id_jugador;
}

NotificarIdJugador::~NotificarIdJugador() {
}


/*
 * NotificarGanador.cpp
 */

#include "NotificarGanador.h"

#include <sstream>
#include "Protocolo.h"
#include "../Utiles/Excepcion.h"

destinatarios_posibles NotificarGanador::destinatarios =
		destinatarios_posibles::todos;

NotificarGanador::NotificarGanador(const std::string & comando_completo)
		throw (std::exception) :
		Mensaje(comando_completo, NotificarGanador::destinatarios) {

	std::istringstream mensaje_a_parsear(comando_completo);

	std::string comando;
	mensaje_a_parsear >> comando;
	mensaje_a_parsear >> this->id_jugador_ganador;

	if (!cantidadArgumentosRecibidosCorrecta(mensaje_a_parsear))
		throw Excepcion(
				"Cantidad de Argumentos recibidos en Comando NOTIFICAR GANADOR no válido.");

	if (comando != NOTIFICAR_GANADOR)
		throw Excepcion("Comando NOTIFICAR GANADOR no válido.");
}

NotificarGanador::NotificarGanador(int id_jugador_ganador) :
		id_jugador_ganador(id_jugador_ganador) {

	this->receptor = getDestinatariosSegunTipoMensaje();
	this->mensaje = serializar();
}

int NotificarGanador::getIdJugadorGanador() const {
	return id_jugador_ganador;
}
destinatarios_posibles NotificarGanador::getDestinatariosSegunTipoMensaje() const {
	return destinatarios;
}

std::string NotificarGanador::serializar() const {
	std::ostringstream notificar_ganador("");
	notificar_ganador << NOTIFICAR_GANADOR << DELIMITADOR_CAMPOS
			<< getIdJugadorGanador() << DELIMITADOR_REGISTROS;
	return notificar_ganador.str();
}

NotificarGanador::~NotificarGanador() {
}


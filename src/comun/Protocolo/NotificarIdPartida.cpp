/*
 * NotificarIdPartida.cpp
 */

#include "NotificarIdPartida.h"

#include "Protocolo.h"
#include <sstream>
#include "../Utiles/Excepcion.h"

destinatarios_posibles NotificarIdPartida::destinatarios =
		destinatarios_posibles::no_es_necesario;

NotificarIdPartida::NotificarIdPartida(const std::string & comando_completo) :
		Mensaje(comando_completo, NotificarIdPartida::destinatarios) {
	std::istringstream mensaje_a_parsear(comando_completo);

	std::string comando;
	mensaje_a_parsear >> comando;
	mensaje_a_parsear >> this->id_partida;

	if (!cantidadArgumentosRecibidosCorrecta(mensaje_a_parsear))
		throw Excepcion(
				"Cantidad de Argumentos recibidos en Comando NOTIFICAR_ID_PARTIDA no válido.");

	if (comando != NOTIFICAR_ID_PARTIDA)
		throw Excepcion("Comando NOTIFICAR_ID_PARTIDA no válido.");


	this->receptor = getDestinatariosSegunTipoMensaje();
	this->mensaje = serializar();

}

NotificarIdPartida::NotificarIdPartida(int id_partida) :
		id_partida(id_partida) {
	this->receptor = getDestinatariosSegunTipoMensaje();
	this->mensaje = serializar();
}

std::string NotificarIdPartida::serializar() const {
	std::ostringstream oss("");
	oss << NOTIFICAR_ID_PARTIDA << DELIMITADOR_CAMPOS << getIdPartida()
			 << DELIMITADOR_REGISTROS;
	return oss.str();
}

destinatarios_posibles NotificarIdPartida::getDestinatariosSegunTipoMensaje() const {
	return destinatarios;
}

int NotificarIdPartida::getIdPartida() const {
	return id_partida;
}

NotificarIdPartida::~NotificarIdPartida() {
}


/*
 * Notificacion.cpp
 */

#include "Notificacion.h"

#include "../Protocolo.h"
#include <sstream>
#include "../../Utiles/Excepcion.h"
#include "../../Codigos.h"

destinatarios_posibles Notificacion::destinatarios =
		destinatarios_posibles::emisor;

bool Notificacion::tipoNotificacionValida(int tipo_notificacion) {
	if ((tipo_notificacion == NOTIFICACION_AVISO)
			|| (tipo_notificacion == NOTIFICACION_ERROR)
			|| (tipo_notificacion == NOTIFICACION_EXITO))
		return true;
	else
		return false;
}

Notificacion::Notificacion(int tipo_notificacion, int id_jugador_destinatario,
		const std::string & notificacion) throw (std::exception) :
		tipo_notificacion(tipo_notificacion), id_jugador_destinatario(
				id_jugador_destinatario), notificacion(notificacion) {

	if (!tipoNotificacionValida(tipo_notificacion))
		throw Excepcion("Tipo de Notificación no válida.");

	this->id_emisor = id_jugador_destinatario;
	this->receptor = getDestinatariosSegunTipoMensaje();
	this->mensaje = serializar();
}

Notificacion::Notificacion(const std::string& comando_completo)
		throw (std::exception) :
		Mensaje(comando_completo, Notificacion::destinatarios) {
	std::istringstream mensaje_a_parsear(comando_completo);

	std::string comando;
	mensaje_a_parsear >> comando;
	mensaje_a_parsear >> this->tipo_notificacion;
	mensaje_a_parsear >> this->id_jugador_destinatario;
	std::getline(mensaje_a_parsear, notificacion);

	if (!cantidadArgumentosRecibidosCorrecta(mensaje_a_parsear))
		throw Excepcion(
				"Cantidad de Argumentos recibidos en Comando NOTIFICACION no válido.");

	if (comando != NOTIFICACION)
		throw Excepcion("Comando NOTIFICACION no válido.");

	if (!tipoNotificacionValida(tipo_notificacion))
		throw Excepcion("Tipo de Notificación no válida.");

	this->id_emisor = id_jugador_destinatario;
	this->receptor = getDestinatariosSegunTipoMensaje();
	this->mensaje = serializar();
}

std::string Notificacion::serializar() const {
	std::ostringstream notificacion;
	notificacion << NOTIFICACION << DELIMITADOR_CAMPOS << getTipoNotificacion()
			<< DELIMITADOR_CAMPOS << getIdJugadorDestinatario()
			<< DELIMITADOR_CAMPOS << getNotificacion() << DELIMITADOR_REGISTROS;
	return notificacion.str();
}

destinatarios_posibles Notificacion::getDestinatariosSegunTipoMensaje() const {
	return destinatarios;
}

int Notificacion::getIdJugadorDestinatario() const {
	return id_jugador_destinatario;
}

const std::string& Notificacion::getNotificacion() const {
	return notificacion;
}

int Notificacion::getTipoNotificacion() const {
	return tipo_notificacion;
}

Notificacion::~Notificacion() {
}

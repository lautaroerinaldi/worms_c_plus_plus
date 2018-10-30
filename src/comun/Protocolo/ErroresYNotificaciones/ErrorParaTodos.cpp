/*
 * ErrorParaTodos.cpp
 */

#include "ErrorParaTodos.h"

#include "../Protocolo.h"
#include "../../Utiles/Excepcion.h"
#include "../../Codigos.h"
#include <sstream>

destinatarios_posibles ErrorParaTodos::destinatarios =
		destinatarios_posibles::todos;

bool ErrorParaTodos::tipoErrorValido(int tipo_de_error) {
	if ((tipo_de_error == NOTIFICACION_AVISO)
			|| (tipo_de_error == NOTIFICACION_ERROR)
			|| (tipo_de_error == NOTIFICACION_EXITO))
		return true;
	else
		return false;
}

ErrorParaTodos::ErrorParaTodos(int tipo_de_error,
		const std::string& mensaje_de_error) throw (std::exception) :
		tipo_de_error(tipo_de_error), mensaje_de_error(mensaje_de_error) {

	if (!tipoErrorValido(tipo_de_error))
		throw Excepcion("Tipo de ERROR PARA TODOS no válido.");

	this->receptor = getDestinatariosSegunTipoMensaje();
	this->mensaje = serializar();
}

ErrorParaTodos::ErrorParaTodos(const std::string & comando_completo)
		throw (std::exception) :
		Mensaje(comando_completo, ErrorParaTodos::destinatarios) {

	std::istringstream mensaje_a_parsear(comando_completo);

	std::string comando;
	mensaje_a_parsear >> comando;
	mensaje_a_parsear >> tipo_de_error;
	std::getline(mensaje_a_parsear, mensaje_de_error);

	if (!cantidadArgumentosRecibidosCorrecta(mensaje_a_parsear))
		throw Excepcion(
				"Cantidad de Argumentos recibidos en Comando ERROR PARA TODOS no válido.");

	if (comando != MENSAJE_DE_ERROR)
		throw Excepcion("Comando ERROR PARA TODOS no válido.");

	if (!tipoErrorValido(tipo_de_error))
		throw Excepcion("Tipo de ERROR PARA TODOS no válido.");

	this->receptor = getDestinatariosSegunTipoMensaje();
	this->mensaje = serializar();
}

destinatarios_posibles ErrorParaTodos::getDestinatariosSegunTipoMensaje() const {
	return destinatarios;
}

const std::string& ErrorParaTodos::getMensajeDeError() const {
	return mensaje_de_error;
}

std::string ErrorParaTodos::serializar() {
	std::ostringstream error;
	error << MENSAJE_DE_ERROR << DELIMITADOR_CAMPOS << getTipoDeError()
			<< DELIMITADOR_CAMPOS << getMensajeDeError()
			<< DELIMITADOR_REGISTROS;
	return error.str();
}

ErrorParaTodos::~ErrorParaTodos() {
}

int ErrorParaTodos::getTipoDeError() const {
	return tipo_de_error;
}

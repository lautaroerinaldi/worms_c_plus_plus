/*
 * DescargarArma.cpp
 */

#include "DescargarArma.h"

#include "../../Utiles/Excepcion.h"

#include <sstream>

destinatarios_posibles DescargarArma::destinatarios =
		destinatarios_posibles::todos;

DescargarArma::DescargarArma() {
	this->receptor = getDestinatariosSegunTipoMensaje();
	this->mensaje = serializar();
}

DescargarArma::~DescargarArma() {
}

std::string DescargarArma::serializar() const {
	std::ostringstream descargar_arma;
	descargar_arma << DESCARGAR_ARMA << DELIMITADOR_REGISTROS;
	return descargar_arma.str();
}

destinatarios_posibles DescargarArma::getDestinatariosSegunTipoMensaje() const {
	return destinatarios;
}

DescargarArma::DescargarArma(const std::string& comando_completo)
		throw (std::exception) {

	std::istringstream mensaje_a_parsear(comando_completo);

	std::string comando;
	mensaje_a_parsear >> comando;

	if (!cantidadArgumentosRecibidosCorrecta(mensaje_a_parsear))
		throw Excepcion(
				"Cantidad de Argumentos recibidos en Comando DESCARGAR ARMA no válido.");

	if (comando != DESCARGAR_ARMA)
		throw Excepcion("Comando DESCARGAR ARMA no válido.");

	this->receptor = getDestinatariosSegunTipoMensaje();
	this->mensaje = serializar();
}

/*
 * Atacar.cpp
 */

#include "Atacar.h"

#include "../Protocolo.h"
#include "../../Utiles/Excepcion.h"

#include <sstream>

destinatarios_posibles Atacar::destinatarios = destinatarios_posibles::todos;

Atacar::Atacar() {
	this->receptor = getDestinatariosSegunTipoMensaje();
	this->mensaje = serializar();
}

std::string Atacar::serializar() const {
	std::ostringstream atacar("");
	atacar << ATACAR << DELIMITADOR_REGISTROS;
	return atacar.str();
}

destinatarios_posibles Atacar::getDestinatariosSegunTipoMensaje() const {
	return destinatarios;
}

Atacar::Atacar(const std::string& comando_completo) throw (std::exception) {
	std::istringstream mensaje_a_parsear(comando_completo);

	std::string comando;
	mensaje_a_parsear >> comando;

	if (!cantidadArgumentosRecibidosCorrecta(mensaje_a_parsear))
		throw Excepcion(
				"Cantidad de Argumentos recibidos en Comando ATACAR no válido.");

	if (comando != ATACAR)
		throw Excepcion("Comando ATACAR no válido.");

	this->receptor = getDestinatariosSegunTipoMensaje();
	this->mensaje = serializar();
}

Atacar::~Atacar() {
}


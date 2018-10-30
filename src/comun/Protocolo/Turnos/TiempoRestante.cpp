/*
 * TiempoRestante.cpp
 */

#include "TiempoRestante.h"

#include "../Protocolo.h"
#include "../../Utiles/Excepcion.h"
#include "../../Codigos.h"

#include <sstream>

destinatarios_posibles TiempoRestante::destinatarios =
		destinatarios_posibles::todos;

TiempoRestante::TiempoRestante(int tiempo_restante)
		throw (std::exception) {

	if (tiempo_restante > 0)
		this->tiempo_restante = tiempo_restante;
	else
		this->tiempo_restante = 0;

	this->receptor = getDestinatariosSegunTipoMensaje();
	this->mensaje = serializar();
}

TiempoRestante::TiempoRestante(const std::string & comando_completo)
		throw (std::exception) :
		Mensaje(comando_completo, TiempoRestante::destinatarios) {
	std::istringstream mensaje_a_parsear(comando_completo);

	std::string comando;
	mensaje_a_parsear >> comando;
	mensaje_a_parsear >> this->tiempo_restante;

	if (comando != TIEMPO_RESTANTE)
		throw Excepcion("Comando TIEMPO RESTANTE no válido.");
}

int TiempoRestante::getTiempoRestante() const {
	return tiempo_restante;
}

std::string TiempoRestante::serializar() const {
	std::ostringstream tiempo_restante;
	tiempo_restante << TIEMPO_RESTANTE << DELIMITADOR_CAMPOS
			<< getTiempoRestante() << DELIMITADOR_REGISTROS;
	return tiempo_restante.str();
}

destinatarios_posibles TiempoRestante::getDestinatariosSegunTipoMensaje() const {
	return destinatarios;
}

TiempoRestante::~TiempoRestante() {
}

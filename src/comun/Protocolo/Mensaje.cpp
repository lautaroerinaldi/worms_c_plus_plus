/*
 * Mensaje.cpp
 */

#include "Mensaje.h"

Mensaje::Mensaje() {
}

Mensaje::Mensaje(int id_emisor, const std::string & mensaje) {
	this->id_emisor = id_emisor;
	this->mensaje = mensaje;
}

Mensaje::Mensaje(const std::string & mensaje, destinatarios_posibles receptor) {
	this->mensaje = mensaje;
	this->receptor = receptor;
}

int Mensaje::getEmisor() {
	return this->id_emisor;
}

std::string Mensaje::getMensaje() {
	return this->mensaje;
}

destinatarios_posibles Mensaje::getReceptor() const {
	return this->receptor;
}

std::string Mensaje::serializar() const {
	return this->mensaje;
}

destinatarios_posibles Mensaje::getDestinatariosSegunTipoMensaje() const {
	return this->receptor;
}

Mensaje::Mensaje(const Mensaje& otro) :
		id_emisor(otro.id_emisor), mensaje(otro.mensaje), receptor(
				otro.receptor) {
}

Mensaje::Mensaje(Mensaje&& otro) :
		id_emisor(otro.id_emisor), mensaje(otro.mensaje), receptor(
				otro.receptor) {
}

bool Mensaje::cantidadArgumentosRecibidosCorrecta(
		const std::istringstream& origen_del_parseo) {
	if (!((origen_del_parseo.eof()) && (!origen_del_parseo.fail())))
		return false;
	else
		return true;
}

Mensaje::~Mensaje() {
}

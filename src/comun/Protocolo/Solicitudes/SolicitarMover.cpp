/*
 * SolicitarMover.cpp
 */

#include "SolicitarMover.h"

#include "../Protocolo.h"
#include "../../Utiles/Excepcion.h"
#include "../../Codigos.h"

#include <sstream>

destinatarios_posibles SolicitarMover::destinatarios =
		destinatarios_posibles::servidor;

bool SolicitarMover::comandoCorrecto(const std::string & comando) const {
	if (comando == getComando())
		return true;
	else
		return false;
}

std::string SolicitarMover::getComando() const {
	return SOLICITAR_MOVER;
}

SolicitarMover::SolicitarMover(const std::string & comando_completo)
		throw (std::exception) :
		Mensaje(comando_completo, SolicitarMover::destinatarios) {

	std::istringstream mensaje_a_parsear(comando_completo);

	std::string comando;
	mensaje_a_parsear >> comando;
	mensaje_a_parsear >> this->direccion;

	if (!cantidadArgumentosRecibidosCorrecta(mensaje_a_parsear))
		throw Excepcion(
				"Cantidad de argumentos " + getComando() + " no válido.");

	if (!direccionValida(direccion))
		throw Excepcion(
				"Dirección de movimiento " + getComando() + " no válida.");
}

int SolicitarMover::getDireccion() const {
	return direccion;
}

SolicitarMover::SolicitarMover(int direccion) throw (std::exception) :
		direccion(direccion) {

	if (!direccionValida(direccion))
		throw Excepcion(
				"Dirección de movimiento en SOLICITAR_MOVER no válida.");

	this->receptor = getDestinatariosSegunTipoMensaje();
	this->mensaje = serializar();
}

SolicitarMover::~SolicitarMover() {
}

destinatarios_posibles SolicitarMover::getDestinatariosSegunTipoMensaje() const {
	return destinatarios;
}

std::string SolicitarMover::serializar() const {
	std::ostringstream solicitar_mover;
	solicitar_mover << getComando() << DELIMITADOR_CAMPOS << getDireccion()
			<< DELIMITADOR_REGISTROS;
	return solicitar_mover.str();
}

bool SolicitarMover::direccionValida(int direccion) {
	if ((direccion == IZQUIERDA) || (direccion == DERECHA))
		return true;
	else
		return false;
}

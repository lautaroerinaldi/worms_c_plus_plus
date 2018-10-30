/*
 * MoverGusano.cpp
 */

#include "MoverGusano.h"

#include "../Protocolo.h"
#include "../../Utiles/Excepcion.h"
#include "../../Codigos.h"

#include <sstream>
#include <math.h>

destinatarios_posibles MoverGusano::destinatarios =
		destinatarios_posibles::todos;

int MoverGusano::getIdGusano() const {
	return id_gusano;
}

int MoverGusano::getInclinacion() const {
	return inclinacion;
}

int MoverGusano::getX() const {
	return x;
}

MoverGusano::MoverGusano(const std::string& comando_completo)
		throw (std::exception) :
		Mensaje(comando_completo, MoverGusano::destinatarios), id_gusano(
		GUSANO_INVALIDO), x(X_INVALIDA), y(Y_INVALIDA), inclinacion(
		INCLINACION_INVALIDA) {
	std::istringstream mensaje_a_parsear(comando_completo);

	std::string comando;
	mensaje_a_parsear >> comando;
	mensaje_a_parsear >> this->id_gusano;

	mensaje_a_parsear >> this->x;
	mensaje_a_parsear >> this->y;
	mensaje_a_parsear >> this->inclinacion;
	mensaje_a_parsear >> this->estado_gusano;

	if (!cantidadArgumentosRecibidosCorrecta(mensaje_a_parsear))
		throw Excepcion(
				"Cantidad de Argumentos recibidos en Comando MOVER GUSANO no válido.");

	if (comando != MOVER_GUSANO)
		throw Excepcion("Comando MOVER GUSANO no válido.");

	if (!inclinacionValida(inclinacion))
		throw Excepcion("Inclinación de movimiento en MOVER GUSANO no válida.");

	if (!estadoGusanoValido(estado_gusano))
		throw Excepcion("ESTADO del gusano en MOVER GUSANO no válido.");

	inicializarEstados();
}

MoverGusano::MoverGusano(int id_gusano, float x, float y, int inclinacion,
		int estado_gusano) throw (std::exception) :
		id_gusano(id_gusano), x(round(x * FACTOR_ESCALA_DE_MODELO_A_VISTA)), y(
				round(y * FACTOR_ESCALA_DE_MODELO_A_VISTA)), inclinacion(
				inclinacion), estado_gusano(estado_gusano) {

	if (!inclinacionValida(inclinacion))
		throw Excepcion("Inclinación de movimiento en MOVER GUSANO no válida.");

	if (!estadoGusanoValido(estado_gusano))
		throw Excepcion("ESTADO del gusano en MOVER GUSANO no válido.");

	this->receptor = getDestinatariosSegunTipoMensaje();
	this->mensaje = serializar();

	inicializarEstados();
}

int MoverGusano::getY() const {
	return y;
}

destinatarios_posibles MoverGusano::getDestinatariosSegunTipoMensaje() const {
	return destinatarios;
}

std::string MoverGusano::serializar() {
	std::ostringstream mover("");
	mover << MOVER_GUSANO << DELIMITADOR_CAMPOS << getIdGusano()
			<< DELIMITADOR_CAMPOS << getX() << DELIMITADOR_CAMPOS << getY()
			<< DELIMITADOR_CAMPOS << getInclinacion() << DELIMITADOR_CAMPOS
			<< getEstadoGusano() <<
			DELIMITADOR_REGISTROS;
	return mover.str();
}

bool MoverGusano::inclinacionValida(int inclinacion) {
	if ((inclinacion == ABAJO) || (inclinacion == NORMAL)
			|| (inclinacion == ARRIBA))
		return true;
	else
		return false;
}

bool MoverGusano::estadoGusanoValido(int estado_gusano) {
	if ((estado_gusano == CAMINANDO) || (estado_gusano == QUIETO)
			|| (estado_gusano == SALTANDO) || (estado_gusano == RETROCESO)
			|| (estado_gusano == CAYENDO) || (estado_gusano == CHOCANDO)
			|| (estado_gusano == VOLANDO))
		return true;
	else
		return false;
}

int MoverGusano::getEstadoGusano() const {
	return estado_gusano;
}

void MoverGusano::inicializarEstados() {
	if (MoverGusano::estados.size() == 0) {
		MoverGusano::estados[CAMINANDO] = CAMINANDO_STR;
		MoverGusano::estados[QUIETO] = QUIETO_STR;
		MoverGusano::estados[SALTANDO] = SALTANDO_STR;
		MoverGusano::estados[RETROCESO] = RETROCESO_STR;
		MoverGusano::estados[CAYENDO] = CAYENDO_STR;
		MoverGusano::estados[CHOCANDO] = CHOCANDO_STR;
		MoverGusano::estados[VOLANDO] = VOLANDO_STR;
	}
}

std::string MoverGusano::getEstadoToString() const {
	return MoverGusano::estados.at(estado_gusano);
}

MoverGusano::~MoverGusano() {
}

/*
 * Teletransportar.cpp
 */

#include "TeletransportarGusano.h"


#include "../Protocolo.h"
#include "../../Utiles/Excepcion.h"
#include "../../Codigos.h"

#include <sstream>
#include <math.h>

destinatarios_posibles TeletransportarGusano::destinatarios =
		destinatarios_posibles::todos;

TeletransportarGusano::TeletransportarGusano(const std::string & comando_completo)
		throw (std::exception) :
		Mensaje(comando_completo, TeletransportarGusano::destinatarios) {

	std::istringstream mensaje_a_parsear(comando_completo);

	std::string comando;
	mensaje_a_parsear >> comando;

	int x_vista;
	int y_vista;

	mensaje_a_parsear >> x_vista;
	mensaje_a_parsear >> y_vista;

	this->x_modelo = ((float)x_vista / (float)FACTOR_ESCALA_DE_MODELO_A_VISTA);
	this->y_modelo = ((float)y_vista / (float)FACTOR_ESCALA_DE_MODELO_A_VISTA);

	if (!cantidadArgumentosRecibidosCorrecta(mensaje_a_parsear))
		throw Excepcion(
				"Cantidad de Argumentos recibidos en Comando TELETRANSPORTAR no válido.");

	if (comando != TELETRANSPORTAR_GUSANO)
		throw Excepcion("Comando TELETRANSPORTAR no válido.");
}

TeletransportarGusano::TeletransportarGusano(float x_modelo, float y_modelo) :
		x_modelo(x_modelo), y_modelo(y_modelo) {

	this->receptor = getDestinatariosSegunTipoMensaje();
	this->mensaje = serializar();
}

int TeletransportarGusano::getXVista() const {
	return round(x_modelo * FACTOR_ESCALA_DE_MODELO_A_VISTA);
}

int TeletransportarGusano::getYVista() const {
	return round(y_modelo * FACTOR_ESCALA_DE_MODELO_A_VISTA);
}

float TeletransportarGusano::getXModelo() const {
	return x_modelo;
}

float TeletransportarGusano::getYModelo() const {
	return y_modelo;
}

destinatarios_posibles TeletransportarGusano::getDestinatariosSegunTipoMensaje() const {
	return destinatarios;
}

std::string TeletransportarGusano::serializar() const {
	std::ostringstream teletransportar;
	teletransportar << TELETRANSPORTAR_GUSANO << DELIMITADOR_CAMPOS <<
	getXVista() << DELIMITADOR_CAMPOS << getYVista() << DELIMITADOR_REGISTROS;
	return teletransportar.str();
}

TeletransportarGusano::~TeletransportarGusano() {
}


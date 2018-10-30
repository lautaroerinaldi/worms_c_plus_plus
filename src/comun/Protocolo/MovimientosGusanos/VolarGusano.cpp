/*
 * Volar.cpp
 */

#include "VolarGusano.h"

#include "../Protocolo.h"
#include "../../Utiles/Excepcion.h"
#include "../../Codigos.h"

#include <sstream>
#include <math.h>

destinatarios_posibles VolarGusano::destinatarios = destinatarios_posibles::todos;

VolarGusano::VolarGusano(const std::string & comando_completo) throw (std::exception) :
		Mensaje(comando_completo, VolarGusano::destinatarios) {

	std::istringstream mensaje_a_parsear(comando_completo);

	std::string comando;
	mensaje_a_parsear >> comando;
	mensaje_a_parsear >> this->id_gusano;

	int x_vista;
	int y_vista;

	mensaje_a_parsear >> x_vista;
	mensaje_a_parsear >> y_vista;

	this->x_modelo =
			((float) x_vista / (float) FACTOR_ESCALA_DE_MODELO_A_VISTA);
	this->y_modelo =
			((float) y_vista / (float) FACTOR_ESCALA_DE_MODELO_A_VISTA);

	mensaje_a_parsear >> this->angulo_en_grados;

	if (!cantidadArgumentosRecibidosCorrecta(mensaje_a_parsear))
		throw Excepcion(
				"Cantidad de Argumentos recibidos en Comando VOLAR GUSANO no válido.");

	if (comando != VOLAR_GUSANO)
		throw Excepcion("Comando VOLAR GUSANO no válido.");
}

VolarGusano::VolarGusano(int id_gusano, float x_modelo, float y_modelo,
		int angulo_en_grados) :
		id_gusano(id_gusano), x_modelo(x_modelo), y_modelo(y_modelo), angulo_en_grados(
				angulo_en_grados) {

	this->receptor = getDestinatariosSegunTipoMensaje();
	this->mensaje = serializar();
}

int VolarGusano::getIdGusano() const {
	return id_gusano;
}

int VolarGusano::getAnguloEnGrados() const {
	return angulo_en_grados;
}

float VolarGusano::getXModelo() const {
	return x_modelo;
}

float VolarGusano::getYModelo() const {
	return y_modelo;
}

int VolarGusano::getXVista() const {
	return round(x_modelo * FACTOR_ESCALA_DE_MODELO_A_VISTA);
}

int VolarGusano::getYVista() const {
	return round(y_modelo * FACTOR_ESCALA_DE_MODELO_A_VISTA);
}

destinatarios_posibles VolarGusano::getDestinatariosSegunTipoMensaje() const {
	return destinatarios;
}

std::string VolarGusano::serializar() const {
	std::ostringstream volar("");
	volar << VOLAR_GUSANO << DELIMITADOR_CAMPOS << getIdGusano() << DELIMITADOR_CAMPOS
			<< getXVista() << DELIMITADOR_CAMPOS << getYVista()
			<< DELIMITADOR_CAMPOS << getAnguloEnGrados()
			<< DELIMITADOR_REGISTROS;
	return volar.str();
}

VolarGusano::~VolarGusano() {
}

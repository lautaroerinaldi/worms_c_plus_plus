/*
 * ImpactarBala.cpp
 */

#include "ImpactarBala.h"

#include <math.h>
#include <sstream>

#include "../../Codigos.h"
#include "../../DefinicionesPrivadas.h"
#include "../../Utiles/Excepcion.h"
#include "../Protocolo.h"

destinatarios_posibles ImpactarBala::destinatarios =
		destinatarios_posibles::todos;

bool ImpactarBala::direccionValida(int direccion) {
	if ((direccion == IZQUIERDA) || (direccion == DERECHA))
		return true;
	else
		return false;
}

ImpactarBala::ImpactarBala(const std::string & comando_completo)
		throw (std::exception) :
		Mensaje(comando_completo, ImpactarBala::destinatarios) {

	std::istringstream mensaje_a_parsear(comando_completo);

	std::string comando;
	mensaje_a_parsear >> comando;
	mensaje_a_parsear >> this->id_bala;

	int x_vista;
	int y_vista;
	int radio_vista;

	mensaje_a_parsear >> x_vista;
	mensaje_a_parsear >> y_vista;
	mensaje_a_parsear >> radio_vista;

	this->x_modelo =
			((float) x_vista / (float) FACTOR_ESCALA_DE_MODELO_A_VISTA);
	this->y_modelo =
			((float) y_vista / (float) FACTOR_ESCALA_DE_MODELO_A_VISTA);
	this->radio_modelo = ((float) radio_vista
			/ (float) FACTOR_ESCALA_DE_MODELO_A_VISTA);

	if (!cantidadArgumentosRecibidosCorrecta(mensaje_a_parsear))
		throw Excepcion(
				"Cantidad de Argumentos recibidos en Comando IMPACTAR BALA no válido.");

	if (comando != IMPACTAR_BALA)
		throw Excepcion("Comando IMPACTAR BALA no válido.");
}

ImpactarBala::ImpactarBala(int id_bala, float x_modelo, float y_modelo,
		float radio_modelo) :
		id_bala(id_bala), x_modelo(x_modelo), y_modelo(y_modelo), radio_modelo(
				radio_modelo) {

	if (this->x_modelo < 0)
		this->x_modelo = 0;

	if (this->y_modelo < 0)
		this->y_modelo = 0;

	if (this->radio_modelo < 0)
		this->radio_modelo = 0;

	this->receptor = getDestinatariosSegunTipoMensaje();
	this->mensaje = serializar();
}

int ImpactarBala::getIdBala() const {
	return id_bala;
}

float ImpactarBala::getXModelo() const {
	return x_modelo;
}

float ImpactarBala::getYModelo() const {
	return y_modelo;
}

int ImpactarBala::getXVista() const {
	return round(x_modelo * FACTOR_ESCALA_DE_MODELO_A_VISTA);
}

int ImpactarBala::getYVista() const {
	return round(y_modelo * FACTOR_ESCALA_DE_MODELO_A_VISTA);
}

float ImpactarBala::getRadioModelo() const {
	return radio_modelo;
}

int ImpactarBala::getRadioVista() const {
	return round(radio_modelo * FACTOR_ESCALA_DE_MODELO_A_VISTA);
}

destinatarios_posibles ImpactarBala::getDestinatariosSegunTipoMensaje() const {
	return destinatarios;
}

std::string ImpactarBala::serializar() const {
	std::ostringstream oss("");
	oss << IMPACTAR_BALA << DELIMITADOR_CAMPOS << getIdBala()
			<< DELIMITADOR_CAMPOS << getXVista() << DELIMITADOR_CAMPOS
			<< getYVista() << DELIMITADOR_CAMPOS << getRadioVista()
			<< DELIMITADOR_REGISTROS;
	return oss.str();
}

ImpactarBala::~ImpactarBala() {
}


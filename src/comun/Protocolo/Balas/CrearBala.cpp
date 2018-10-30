/*
 * CrearBala.cpp
 */

#include "CrearBala.h"

#include "../Protocolo.h"
#include "../../Utiles/Excepcion.h"
#include "../../Codigos.h"

#include <sstream>
#include <math.h>

destinatarios_posibles CrearBala::destinatarios = destinatarios_posibles::todos;

bool CrearBala::direccionValida(int direccion) {
	if ((direccion == IZQUIERDA) || (direccion == DERECHA))
		return true;
	else
		return false;
}

bool CrearBala::tipoArmaValida(int tipo_arma) {
	if ((tipo_arma == BAZOOKA) || (tipo_arma == BANANA)
			|| (tipo_arma == MORTERO) || (tipo_arma == GRANADA_ROJA)
			|| (tipo_arma == GRANADA_VERDE) || (tipo_arma == GRANADA_SANTA)
			|| (tipo_arma == DINAMITA) || (tipo_arma == ATAQUE_AEREO)
			|| (tipo_arma == BATE_DE_BASEBALL)
			|| (tipo_arma == TELETRANSPORTACION))
		return true;
	else
		return false;
}

CrearBala::CrearBala(const std::string & comando_completo)
		throw (std::exception) :
		Mensaje(comando_completo, CrearBala::destinatarios) {

	std::istringstream mensaje_a_parsear(comando_completo);

	std::string comando;
	mensaje_a_parsear >> comando;
	mensaje_a_parsear >> this->id_bala;

	int x_vista;
	int y_vista;

	mensaje_a_parsear >> x_vista;
	mensaje_a_parsear >> y_vista;

	this->x_modelo =
			((float) x_vista / (float) FACTOR_ESCALA_DE_MODELO_A_VISTA);
	this->y_modelo =
			((float) y_vista / (float) FACTOR_ESCALA_DE_MODELO_A_VISTA);

	mensaje_a_parsear >> this->angulo_en_grados;
	mensaje_a_parsear >> this->direccion;
	mensaje_a_parsear >> this->tipo_arma;

	if (!cantidadArgumentosRecibidosCorrecta(mensaje_a_parsear))
		throw Excepcion(
				"Cantidad de Argumentos recibidos en Comando CREAR BALA no válido.");

	if (comando != CREAR_BALA)
		throw Excepcion("Comando CREAR BALA no válido.");

	if (!direccionValida(direccion))
		throw Excepcion("Dirección de movimiento en CREAR BALA no válida.");
}

CrearBala::CrearBala(int id_bala, float x_modelo, float y_modelo,
		float angulo_en_grados, int direccion, int tipo_arma)
				throw (std::exception) :
		id_bala(id_bala), x_modelo(x_modelo), y_modelo(y_modelo), angulo_en_grados(
				angulo_en_grados), direccion(direccion), tipo_arma(tipo_arma) {
	if (!direccionValida(direccion))
		throw Excepcion("Dirección de movimiento en CREAR BALA no válida.");

	if (this->x_modelo < 0)
		this->x_modelo = 0;

	if (this->y_modelo < 0)
		this->y_modelo = 0;

	if (this->angulo_en_grados < 0)
		this->angulo_en_grados = 0;

	if (!tipoArmaValida(tipo_arma))
		throw Excepcion("Tipo de Arma en CREAR BALA no válida.");

	this->receptor = getDestinatariosSegunTipoMensaje();
	this->mensaje = serializar();
}

int CrearBala::getAnguloEnGrados() const {
	return round(angulo_en_grados);
}

int CrearBala::getDireccion() const {
	return direccion;
}

int CrearBala::getIdBala() const {
	return id_bala;
}

float CrearBala::getXModelo() const {
	return x_modelo;
}

float CrearBala::getYModelo() const {
	return y_modelo;
}

int CrearBala::getXVista() const {
	return round(x_modelo * FACTOR_ESCALA_DE_MODELO_A_VISTA);
}

int CrearBala::getYVista() const {
	return round(y_modelo * FACTOR_ESCALA_DE_MODELO_A_VISTA);
}

destinatarios_posibles CrearBala::getDestinatariosSegunTipoMensaje() const {
	return destinatarios;
}

std::string CrearBala::serializar() const {
	std::ostringstream crear_bala;
	crear_bala.clear();
	crear_bala << CREAR_BALA << DELIMITADOR_CAMPOS << getIdBala()
			<< DELIMITADOR_CAMPOS << getXVista() << DELIMITADOR_CAMPOS
			<< getYVista() << DELIMITADOR_CAMPOS << getAnguloEnGrados()
			<< DELIMITADOR_CAMPOS << getDireccion() << DELIMITADOR_CAMPOS
			<< getTipoArma() << DELIMITADOR_REGISTROS;
	return crear_bala.str();
}

CrearBala::~CrearBala() {
}

int CrearBala::getTipoArma() const {
	return tipo_arma;
}

/*
 * MoverBala.cpp
 */

#include "MoverBala.h"

#include <math.h>
#include <sstream>

#include "../../Codigos.h"
#include "../../DefinicionesPrivadas.h"
#include "../../Utiles/Excepcion.h"
#include "../Protocolo.h"

destinatarios_posibles MoverBala::destinatarios = destinatarios_posibles::todos;

bool MoverBala::direccionValida(int direccion) {
	if ((direccion == IZQUIERDA) || (direccion == DERECHA))
		return true;
	else
		return false;
}

MoverBala::MoverBala(const std::string & comando_completo)
		throw (std::exception) :
		Mensaje(comando_completo, MoverBala::destinatarios) {

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

	if (!cantidadArgumentosRecibidosCorrecta(mensaje_a_parsear))
		throw Excepcion(
				"Cantidad de Argumentos recibidos en Comando MOVER BALA no válido.");

	if (comando != MOVER_BALA)
		throw Excepcion("Comando MOVER BALA no válido.");

	if (!direccionValida(direccion))
		throw Excepcion("Dirección de movimiento en MOVER BALA no válida.");
}

MoverBala::MoverBala(int id_bala, float x_modelo, float y_modelo,
		float angulo_en_grados, int direccion) throw (std::exception) :
		id_bala(id_bala), x_modelo(x_modelo), y_modelo(y_modelo), angulo_en_grados(
				angulo_en_grados), direccion(direccion) {

	if (this->x_modelo < 0)
		this->x_modelo = 0;

	if (this->y_modelo < 0)
		this->y_modelo = 0;

	if (this->angulo_en_grados < 0)
		this->angulo_en_grados = 0;

	if (!direccionValida(direccion))
		throw Excepcion("Dirección de movimiento en MOVER BALA no válida.");

	this->receptor = getDestinatariosSegunTipoMensaje();
	this->mensaje = serializar();
}

int MoverBala::getAnguloEnGrados() const {
	return round(angulo_en_grados);
}

int MoverBala::getDireccion() const {
	return direccion;
}

int MoverBala::getIdBala() const {
	return id_bala;
}

float MoverBala::getXModelo() const {
	return x_modelo;
}

float MoverBala::getYModelo() const {
	return y_modelo;
}

int MoverBala::getXVista() const {
	return round(x_modelo * FACTOR_ESCALA_DE_MODELO_A_VISTA);
}

int MoverBala::getYVista() const {
	return round(y_modelo * FACTOR_ESCALA_DE_MODELO_A_VISTA);
}

destinatarios_posibles MoverBala::getDestinatariosSegunTipoMensaje() const {
	return destinatarios;
}

std::string MoverBala::serializar() const {
	std::ostringstream oss("");
	oss << MOVER_BALA << DELIMITADOR_CAMPOS << getIdBala() << DELIMITADOR_CAMPOS
			<< getXVista() << DELIMITADOR_CAMPOS << getYVista()
			<< DELIMITADOR_CAMPOS << getAnguloEnGrados() << DELIMITADOR_CAMPOS
			<< getDireccion() << DELIMITADOR_REGISTROS;
	return oss.str();
}

MoverBala::~MoverBala() {
}


/*
 * CrearGusano.cpp
 */

#include "CrearGusano.h"

#include "../Protocolo.h"
#include <sstream>
#include "../../Utiles/Excepcion.h"
#include <math.h>
#include "../../Codigos.h"

destinatarios_posibles CrearGusano::destinatarios =
		destinatarios_posibles::todos;

int CrearGusano::getIdGusano() const {
	return id_gusano;
}

int CrearGusano::getIdJugador() const {
	return id_jugador;
}

int CrearGusano::getVida() const {
	return vida;
}

int CrearGusano::getX() const {
	return x;
}

int CrearGusano::getY() const {
	return y;
}

int CrearGusano::getInclinacion() const {
	return inclinacion;
}

CrearGusano::CrearGusano(const std::string& comando_completo)
		throw (std::exception) :
		Mensaje(comando_completo, CrearGusano::destinatarios) {

	std::istringstream mensaje_a_parsear(comando_completo);

	std::string comando;
	mensaje_a_parsear >> comando;
	mensaje_a_parsear >> this->id_gusano;
	mensaje_a_parsear >> this->id_jugador;
	mensaje_a_parsear >> this->vida;
	mensaje_a_parsear >> this->x;
	mensaje_a_parsear >> this->y;
	mensaje_a_parsear >> this->inclinacion;

	if (!cantidadArgumentosRecibidosCorrecta(mensaje_a_parsear))
		throw Excepcion(
				"Cantidad de Argumentos recibidos en Comando CREAR GUSANO no válido.");

	if (comando != CREAR_GUSANO)
		throw Excepcion("Comando CREAR GUSANO no válido.");

	this->receptor = getDestinatariosSegunTipoMensaje();
	this->mensaje = serializar();
}

CrearGusano::CrearGusano(int id_gusano, int id_jugador, int vida, float x,
		float y, int inclinacion) :
		id_gusano(id_gusano), id_jugador(id_jugador), vida(vida), x(
				round(x * FACTOR_ESCALA_DE_MODELO_A_VISTA)), y(
				round(y * FACTOR_ESCALA_DE_MODELO_A_VISTA)), inclinacion(
				inclinacion) {

	this->receptor = getDestinatariosSegunTipoMensaje();
	this->mensaje = serializar();

}

destinatarios_posibles CrearGusano::getDestinatariosSegunTipoMensaje() const {
	return destinatarios;
}

std::string CrearGusano::serializar() {
	std::ostringstream crear_gusano;
	crear_gusano << CREAR_GUSANO << DELIMITADOR_CAMPOS << getIdGusano()
			<< DELIMITADOR_CAMPOS << getIdJugador() << DELIMITADOR_CAMPOS
			<< getVida() << DELIMITADOR_CAMPOS << getX() << DELIMITADOR_CAMPOS
			<< getY() << DELIMITADOR_CAMPOS << getInclinacion()
			<< DELIMITADOR_REGISTROS;
	return crear_gusano.str();
}

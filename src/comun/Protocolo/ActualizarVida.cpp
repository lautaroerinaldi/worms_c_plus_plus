/*
 * ActualizarVida.cpp
 */

#include "ActualizarVida.h"
#include "Protocolo.h"

#include "../Codigos.h"
#include "../Utiles/Excepcion.h"

#include <sstream>

destinatarios_posibles ActualizarVida::destinatarios =
		destinatarios_posibles::todos;

bool ActualizarVida::inclinacionValida(int inclinacion) {
	if ((inclinacion == ABAJO) || (inclinacion == NORMAL)
			|| (inclinacion == ARRIBA))
		return true;
	else
		return false;
}

ActualizarVida::ActualizarVida(int id_gusano, int vida, int inclinacion)
		throw (std::exception) :
		id_gusano(id_gusano), vida(vida), inclinacion(inclinacion) {

	if (!inclinacionValida(inclinacion))
		throw Excepcion(
				"Inclinación de movimiento en ACTUALIZAR VIDA no válida.");

	this->receptor = getDestinatariosSegunTipoMensaje();
	this->mensaje = serializar();
}

ActualizarVida::ActualizarVida(const std::string& comando_completo)
		throw (std::exception) :
		Mensaje(comando_completo, ActualizarVida::destinatarios) {
	std::istringstream mensaje_a_parsear(comando_completo);

	std::string comando;
	mensaje_a_parsear >> comando;
	mensaje_a_parsear >> this->id_gusano;
	mensaje_a_parsear >> this->vida;
	mensaje_a_parsear >> this->inclinacion;

	if (!cantidadArgumentosRecibidosCorrecta(mensaje_a_parsear))
		throw Excepcion(
				"Cantidad de Argumentos recibidos en Comando ACTUALIZAR VIDA no válido.");

	if (comando != ACTUALIZAR_VIDA)
		throw Excepcion("Comando ACTUALIZAR VIDA  no válido.");

	if (!inclinacionValida(inclinacion))
		throw Excepcion(
				"Inclinación de movimiento en ACTUALIZAR VIDA no válida.");
}

int ActualizarVida::getVida() const {
	return vida;
}

int ActualizarVida::getIdGusano() const {
	return id_gusano;
}

int ActualizarVida::getInclinacion() const {
	return inclinacion;
}

std::string ActualizarVida::serializar() const {
	std::ostringstream actualizar_vida;
	actualizar_vida << ACTUALIZAR_VIDA << DELIMITADOR_CAMPOS << getIdGusano()
			<< DELIMITADOR_CAMPOS << getVida() << DELIMITADOR_CAMPOS
			<< getInclinacion() << DELIMITADOR_REGISTROS;
	return actualizar_vida.str();
}

destinatarios_posibles ActualizarVida::getDestinatariosSegunTipoMensaje() const {
	return destinatarios;
}

ActualizarVida::~ActualizarVida() {
}


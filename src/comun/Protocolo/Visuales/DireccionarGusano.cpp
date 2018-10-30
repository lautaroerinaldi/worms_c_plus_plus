/*
 * Direccionar.cpp
 */

#include "DireccionarGusano.h"

#include "../Protocolo.h"
#include "../../Utiles/Excepcion.h"
#include "../../Codigos.h"

#include <sstream>

destinatarios_posibles DireccionarGusano::destinatarios =
		destinatarios_posibles::todos;

bool DireccionarGusano::direccionValida(int direccion) {
	if ((direccion == IZQUIERDA) || (direccion == DERECHA))
		return true;
	else
		return false;
}

DireccionarGusano::DireccionarGusano(const std::string & comando_completo)
		throw (std::exception) :
		Mensaje(comando_completo, DireccionarGusano::destinatarios) {
	std::istringstream mensaje_a_parsear(comando_completo);
	std::string comando;
	mensaje_a_parsear >> comando;
	mensaje_a_parsear >> this->direccion;

	if (!cantidadArgumentosRecibidosCorrecta(mensaje_a_parsear))
		throw Excepcion(
				"Cantidad de Argumentos recibidos en Comando DIRECCIONAR no válido.");

	if (comando != DIRECCIONAR_GUSANO)
		throw Excepcion("Comando DIRECCIONAR no válido.");

	if (!direccionValida(direccion))
		throw Excepcion("Dirección de movimiento en DIRECCIONAR no válida.");
}

DireccionarGusano::DireccionarGusano(int direccion) throw (std::exception) :
		direccion(direccion) {

	if (!direccionValida(direccion))
		throw Excepcion("Dirección de movimiento en DIRECCIONAR no válida.");

	this->receptor = getDestinatariosSegunTipoMensaje();
	this->mensaje = serializar();
}

int DireccionarGusano::getDireccion() const {
	return direccion;
}

destinatarios_posibles DireccionarGusano::getDestinatariosSegunTipoMensaje() const {
	return destinatarios;
}

std::string DireccionarGusano::serializar() {
	std::ostringstream direccionar("");
	direccionar << DIRECCIONAR_GUSANO << DELIMITADOR_CAMPOS << getDireccion()
			<< DELIMITADOR_REGISTROS;
	return direccionar.str();
}

DireccionarGusano::~DireccionarGusano() {
}


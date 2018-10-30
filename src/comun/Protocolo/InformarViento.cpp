/*
 * InformarViento.cpp
 */

#include "InformarViento.h"

#include "Protocolo.h"
#include "../Codigos.h"
#include "../Utiles/Excepcion.h"

#include <sstream>
#include <math.h>

destinatarios_posibles InformarViento::destinatarios =
		destinatarios_posibles::todos;

bool InformarViento::direccionValida(int direccion) {
	if ((direccion == IZQUIERDA) || (direccion == DERECHA))
		return true;
	else
		return false;
}

InformarViento::InformarViento(
		float magnitud_viento_en_metros_por_segundo_sin_signo, int direccion)
				throw (std::exception) :
		magnitud_viento_en_metros_por_segundo_sin_signo(
				magnitud_viento_en_metros_por_segundo_sin_signo), direccion(
				direccion) {

	if (!direccionValida(direccion))
		throw Excepcion("Dirección en INFORMAR VIENTO no válida.");

	this->receptor = getDestinatariosSegunTipoMensaje();
	this->mensaje = serializar();
}

InformarViento::InformarViento(const std::string& comando_completo)
		throw (std::exception) :
		Mensaje(comando_completo, InformarViento::destinatarios) {
	std::istringstream mensaje_a_parsear(comando_completo);

	std::string comando;
	mensaje_a_parsear >> comando;

	int magnitud_viento_en_centimetros_por_segundo;
	mensaje_a_parsear >> magnitud_viento_en_centimetros_por_segundo;
	this->magnitud_viento_en_metros_por_segundo_sin_signo =
			(float) magnitud_viento_en_centimetros_por_segundo / 100;

	mensaje_a_parsear >> this->direccion;

	if (!cantidadArgumentosRecibidosCorrecta(mensaje_a_parsear))
		throw Excepcion(
				"Cantidad de Argumentos recibidos en Comando INFORMAR VIENTO no válido.");

	if (comando != INFORMAR_VIENTO)
		throw Excepcion("Comando INFORMAR VIENTO no válido.");

	if (!direccionValida(direccion))
		throw Excepcion("Dirección en INFORMAR VIENTO no válida.");
}

int InformarViento::getDireccion() const {
	return direccion;
}

int InformarViento::getMagnitudVientoEnCentimetrosPorSegundo() const {
	return round(magnitud_viento_en_metros_por_segundo_sin_signo * 100);
}

std::string InformarViento::serializar() const {
	std::ostringstream informar_viento;
	informar_viento << INFORMAR_VIENTO << DELIMITADOR_CAMPOS
			<< getMagnitudVientoEnCentimetrosPorSegundo() << DELIMITADOR_CAMPOS
			<<
			getDireccion() << DELIMITADOR_REGISTROS;
	return informar_viento.str();
}

destinatarios_posibles InformarViento::getDestinatariosSegunTipoMensaje() const {
	return destinatarios;
}

InformarViento::~InformarViento() {
}

/*
 * CrearViga.cpp
 */

#include "CrearViga.h"

#include "../Protocolo.h"
#include <sstream>
#include "../../Utiles/Excepcion.h"
#include "../../Codigos.h"
#include <math.h>

destinatarios_posibles CrearViga::destinatarios = destinatarios_posibles::todos;

bool CrearViga::anguloEnGradosValido(int angulo_en_grados) const {
	if ((angulo_en_grados == VIGA_ANGULO_GRADOS_0)
			|| (angulo_en_grados == VIGA_ANGULO_GRADOS_45)
			|| (angulo_en_grados == VIGA_ANGULO_GRADOS_60)
			|| (angulo_en_grados == VIGA_ANGULO_GRADOS_90)
			|| (angulo_en_grados == VIGA_ANGULO_GRADOS_120)
			|| (angulo_en_grados == VIGA_ANGULO_GRADOS_135))
		return true;
	else
		return false;
}

bool CrearViga::longitudVigaValida(float longitud_en_metros) const {
	if ((longitud_en_metros == LONGITUD_VIGA_CORTA_EN_METROS)
			|| (longitud_en_metros == LONGITUD_VIGA_LARGA_EN_METROS))
		return true;
	else
		return false;
}

int CrearViga::getAnguloEnGrados() const {
	return angulo_en_grados;
}

int CrearViga::getLongitud() const {
	return longitud_en_metros;
}

int CrearViga::getX() const {
	return x;
}

int CrearViga::getY() const {
	return y;
}

CrearViga::CrearViga(const std::string& comando_completo) throw (std::exception) :
		Mensaje(comando_completo, CrearViga::destinatarios) {

	std::istringstream mensaje_a_parsear(comando_completo);

	std::string comando;
	mensaje_a_parsear >> comando;
	mensaje_a_parsear >> this->longitud_en_metros;
	mensaje_a_parsear >> this->x;
	mensaje_a_parsear >> this->y;
	mensaje_a_parsear >> this->angulo_en_grados;

	if (!cantidadArgumentosRecibidosCorrecta(mensaje_a_parsear))
		throw Excepcion(
				"Cantidad de Argumentos recibidos en Comando CREAR VIGA no válido.");

	if (comando != CREAR_VIGA)
		throw Excepcion("Comando CREAR VIGA no válido.");

	if (!anguloEnGradosValido(angulo_en_grados))
		throw Excepcion("El ángulo de la Viga no es válido.");

	this->receptor = getDestinatariosSegunTipoMensaje();
	this->mensaje = serializar();
}

CrearViga::CrearViga(float longitud_en_metros, float x, float y,
		int angulo_en_grados) :
		longitud_en_metros(
				round(longitud_en_metros * FACTOR_ESCALA_DE_MODELO_A_VISTA)), x(
				round(x * FACTOR_ESCALA_DE_MODELO_A_VISTA)), y(
				round(y * FACTOR_ESCALA_DE_MODELO_A_VISTA)), angulo_en_grados(
				angulo_en_grados) {

	if (!anguloEnGradosValido(angulo_en_grados))
		throw Excepcion("El ángulo de la Viga no es válido.");

	if (!longitudVigaValida(longitud_en_metros))
		throw Excepcion("La longitud de la Viga no es válida.");

	this->receptor = getDestinatariosSegunTipoMensaje();
	this->mensaje = serializar();

}

destinatarios_posibles CrearViga::getDestinatariosSegunTipoMensaje() const {
	return destinatarios;
}

std::string CrearViga::serializar() {
	std::ostringstream crear_viga;
	crear_viga << CREAR_VIGA << DELIMITADOR_CAMPOS << getLongitud()
			<< DELIMITADOR_CAMPOS << getX() << DELIMITADOR_CAMPOS << getY()
			<< DELIMITADOR_CAMPOS << getAnguloEnGrados() <<
			DELIMITADOR_REGISTROS;
	return crear_viga.str();
}

float CrearViga::convertirARadianes(int angulo_en_grados) const {
	return ((angulo_en_grados * M_PI) / 180);
}

float CrearViga::getAnguloEnRadianes() const {
	return convertirARadianes(getAnguloEnGrados());
}

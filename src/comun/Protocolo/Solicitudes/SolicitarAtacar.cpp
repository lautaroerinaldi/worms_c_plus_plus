/*
 * SolicitarAtacar.cpp
 */

#include "SolicitarAtacar.h"

#include "../Protocolo.h"
#include "../../Utiles/Excepcion.h"
#include "../../Codigos.h"

#include <sstream>
#include <math.h>

destinatarios_posibles SolicitarAtacar::destinatarios =
		destinatarios_posibles::servidor;

bool SolicitarAtacar::direccionValida(int direccion) {
	if ((direccion == IZQUIERDA) || (direccion == DERECHA))
		return true;
	else
		return false;
}

SolicitarAtacar::SolicitarAtacar(const std::string & comando_completo)
		throw (std::exception) :
		Mensaje(comando_completo, SolicitarAtacar::destinatarios) {

	std::istringstream mensaje_a_parsear(comando_completo);

	std::string comando;
	mensaje_a_parsear >> comando;
	mensaje_a_parsear >> this->angulo_en_grados;
	mensaje_a_parsear >> this->direccion;
	mensaje_a_parsear >> this->potencia;
	mensaje_a_parsear >> this->conteo;
	mensaje_a_parsear >> this->x_vista;
	mensaje_a_parsear >> this->y_vista;

	if (!cantidadArgumentosRecibidosCorrecta(mensaje_a_parsear))
		throw Excepcion(
				"Cantidad de Argumentos recibidos en Comando SOLICITAR ATACAR no válido.");

	if (comando != SOLICITAR_ATACAR)
		throw Excepcion("Comando SOLICITAR ATACAR no válido.");
}

SolicitarAtacar::SolicitarAtacar(int angulo_en_grados, int direccion,
		int potencia, int conteo, int x_vista, int y_vista)
				throw (std::exception) :
		angulo_en_grados(angulo_en_grados), direccion(direccion), potencia(
				potencia), conteo(conteo), x_vista(x_vista), y_vista(y_vista) {

	this->receptor = getDestinatariosSegunTipoMensaje();
	this->mensaje = serializar();
}

int SolicitarAtacar::getAnguloEnGrados() const {
	return angulo_en_grados;
}

int SolicitarAtacar::getConteo() const {
	return conteo;
}

int SolicitarAtacar::getDireccion() const {
	return direccion;
}

int SolicitarAtacar::getPotencia() const {
	return potencia;
}

int SolicitarAtacar::getXVista() const {
	return x_vista;
}

int SolicitarAtacar::getYVista() const {
	return y_vista;
}

float SolicitarAtacar::getXModelo() const {
	return ((float)x_vista / (float)FACTOR_ESCALA_DE_MODELO_A_VISTA);
}

float SolicitarAtacar::getYModelo() const {
	return ((float)y_vista / (float)FACTOR_ESCALA_DE_MODELO_A_VISTA);
}

destinatarios_posibles SolicitarAtacar::getDestinatariosSegunTipoMensaje() const {
	return destinatarios;
}

std::string SolicitarAtacar::serializar() const {
	std::ostringstream solicitar_atacar;
	solicitar_atacar << SOLICITAR_ATACAR << DELIMITADOR_CAMPOS
			<< getAnguloEnGrados() << DELIMITADOR_CAMPOS << getDireccion()
			<< DELIMITADOR_CAMPOS << getPotencia() << DELIMITADOR_CAMPOS
			<< getConteo() << DELIMITADOR_CAMPOS << getXVista()
			<< DELIMITADOR_CAMPOS << getYVista() << DELIMITADOR_REGISTROS;
	return solicitar_atacar.str();
}

SolicitarAtacar::~SolicitarAtacar() {
}


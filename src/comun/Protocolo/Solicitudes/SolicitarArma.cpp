/*
 * SolicitarArma.cpp
 */

#include "SolicitarArma.h"

#include "../../Utiles/Excepcion.h"
#include "../../Codigos.h"

#include <sstream>

destinatarios_posibles SolicitarArma::destinatarios =
		destinatarios_posibles::servidor;

bool SolicitarArma::tipoArmaValida(int tipo_arma) {
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

SolicitarArma::SolicitarArma(const std::string& comando_completo)
		throw (std::exception) :
		Mensaje(comando_completo, SolicitarArma::destinatarios), tipo_arma(
		ARMA_INVALIDA) {

	std::istringstream mensaje_a_parsear(comando_completo);

	std::string comando;
	mensaje_a_parsear >> comando;
	mensaje_a_parsear >> tipo_arma;

	if (!cantidadArgumentosRecibidosCorrecta(mensaje_a_parsear))
		throw Excepcion(
				"Cantidad de Argumentos recibidos en Comando SOLICITAR_ARMA no válido.");

	if (comando != SOLICITAR_ARMA)
		throw Excepcion("Comando SOLICITAR_ARMA no válido.");

	if (!tipoArmaValida(tipo_arma))
		throw Excepcion("Tipo de Arma no válida.");
}

SolicitarArma::SolicitarArma(int tipo_arma) throw (std::exception) :
		tipo_arma(tipo_arma) {

	if (!tipoArmaValida(tipo_arma))
		throw Excepcion("Tipo de Arma no válida.");

	this->receptor = getDestinatariosSegunTipoMensaje();
	this->mensaje = serializar();
}

std::string SolicitarArma::serializar() const {
	std::ostringstream solicitar_arma;
	solicitar_arma << SOLICITAR_ARMA << DELIMITADOR_CAMPOS << getTipoArma()
			<< DELIMITADOR_REGISTROS;
	return solicitar_arma.str();
}

destinatarios_posibles SolicitarArma::getDestinatariosSegunTipoMensaje() const {
	return destinatarios;
}

int SolicitarArma::getTipoArma() const {
	return tipo_arma;
}

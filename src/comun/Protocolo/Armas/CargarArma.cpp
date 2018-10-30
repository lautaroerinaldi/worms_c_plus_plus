/*
 * CargarArma.cpp
 */

#include "CargarArma.h"

#include "../../Utiles/Excepcion.h"
#include "../../Codigos.h"

#include <sstream>

destinatarios_posibles CargarArma::destinatarios = destinatarios_posibles::todos;

int CargarArma::getIdGusano() const {
	return id_gusano;
}

bool CargarArma::tipoArmaValida(int tipo_arma) {
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

CargarArma::CargarArma(const std::string& comando_completo)
		throw (std::exception) :
		Mensaje(comando_completo, CargarArma::destinatarios), id_gusano(
		GUSANO_INVALIDO), tipo_arma(ARMA_INVALIDA) {
	std::istringstream mensaje_a_parsear(comando_completo);

	std::string comando;
	mensaje_a_parsear >> comando;
	mensaje_a_parsear >> this->id_gusano;
	mensaje_a_parsear >> this->tipo_arma;

	if (!cantidadArgumentosRecibidosCorrecta(mensaje_a_parsear))
		throw Excepcion(
				"Cantidad de Argumentos recibidos en Comando CARGAR_ARMA no válido.");

	if (comando != CARGAR_ARMA)
		throw Excepcion("Comando CARGAR_ARMA no válido.");

	if (!tipoArmaValida(tipo_arma))
		throw Excepcion("Tipo de Arma en CARGAR_ARMA no válida.");
}

CargarArma::CargarArma(int id_gusano, int tipo_arma) throw (std::exception) :
		id_gusano(id_gusano), tipo_arma(tipo_arma) {
	if (!tipoArmaValida(tipo_arma))
		throw Excepcion("Tipo de Arma en CARGAR_ARMA no válida.");

	this->receptor = getDestinatariosSegunTipoMensaje();
	this->mensaje = serializar();
}

destinatarios_posibles CargarArma::getDestinatariosSegunTipoMensaje() const {
	return destinatarios;
}

int CargarArma::getTipoArma() const {
	return tipo_arma;
}

std::string CargarArma::serializar() {
	std::ostringstream cargar_arma;
	cargar_arma << CARGAR_ARMA << DELIMITADOR_CAMPOS << getIdGusano()
			<< DELIMITADOR_CAMPOS << getTipoArma() << DELIMITADOR_REGISTROS;
	return cargar_arma.str();
}


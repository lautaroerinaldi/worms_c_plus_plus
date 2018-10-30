/*
 * DestruirBala.cpp
 */

#include "DestruirBala.h"

#include "../Protocolo.h"
#include "../../Utiles/Excepcion.h"

#include <sstream>

destinatarios_posibles DestruirBala::destinatarios =
		destinatarios_posibles::todos;

DestruirBala::DestruirBala(const std::string & comando_completo)
		throw (std::exception) :
		Mensaje(comando_completo, DestruirBala::destinatarios) {

	std::istringstream mensaje_a_parsear(comando_completo);

	std::string comando;
	mensaje_a_parsear >> comando;
	mensaje_a_parsear >> this->id_bala;

	if (!cantidadArgumentosRecibidosCorrecta(mensaje_a_parsear))
		throw Excepcion(
				"Cantidad de Argumentos recibidos en Comando DESTRUIR BALA no válido.");

	if (comando != DESTRUIR_BALA)
		throw Excepcion("Comando DESTRUIR BALA no válido.");
}

DestruirBala::DestruirBala(int id_bala) :
		id_bala(id_bala) {
	this->receptor = getDestinatariosSegunTipoMensaje();
	this->mensaje = serializar();
}

int DestruirBala::getIdBala() const {
	return id_bala;
}

destinatarios_posibles DestruirBala::getDestinatariosSegunTipoMensaje() const {
	return destinatarios;
}

std::string DestruirBala::serializar() const {
	std::ostringstream destruir_bala("");
	destruir_bala << DESTRUIR_BALA << DELIMITADOR_CAMPOS << getIdBala()
			<< DELIMITADOR_REGISTROS;
	return destruir_bala.str();
}

DestruirBala::~DestruirBala() {
}


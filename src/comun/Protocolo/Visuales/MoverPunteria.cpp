/*
 * MoverPunteria.cpp
 */

#include "MoverPunteria.h"

#include "../Protocolo.h"
#include "../../Codigos.h"
#include "../../Utiles/Excepcion.h"

#include <sstream>

destinatarios_posibles MoverPunteria::destinatarios =
		destinatarios_posibles::todos;

bool MoverPunteria::punteriaValida(int punteria) {
	if ((punteria == SUBIR_PUNTERIA) || (punteria == BAJAR_PUNTERIA))
		return true;
	else
		return false;
}

MoverPunteria::MoverPunteria(int punteria) {
	this->punteria = punteria;
	if (!punteriaValida(punteria))
		throw Excepcion("Puntería no válida.");

	this->receptor = getDestinatariosSegunTipoMensaje();
	this->mensaje = serializar();
}

MoverPunteria::MoverPunteria(const std::string & comando_completo)
		throw (std::exception) {
	std::istringstream mensaje_a_parsear(comando_completo);

	std::string comando;
	mensaje_a_parsear >> comando;
	mensaje_a_parsear >> punteria;

	if (!cantidadArgumentosRecibidosCorrecta(mensaje_a_parsear))
		throw Excepcion(
				"Cantidad de Argumentos recibidos en Comando MOVER PUNTERIA no válido.");

	if (comando != MOVER_PUNTERIA)
		throw Excepcion("Comando MOVER PUNTERÍA no válido.");

	if (!punteriaValida(punteria))
		throw Excepcion("Puntería no válida.");

	this->receptor = getDestinatariosSegunTipoMensaje();
	this->mensaje = serializar();
}

int MoverPunteria::getPunteria() const {
	return punteria;
}

std::string MoverPunteria::serializar() {
	std::ostringstream mover_punteria;
	mover_punteria << MOVER_PUNTERIA << DELIMITADOR_CAMPOS << getPunteria()
			<< DELIMITADOR_REGISTROS;
	return mover_punteria.str();
}

destinatarios_posibles MoverPunteria::getDestinatariosSegunTipoMensaje() const {
	return destinatarios;
}

MoverPunteria::~MoverPunteria() {
}

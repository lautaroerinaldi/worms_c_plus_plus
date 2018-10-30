/*
 * UnirseAPartida.cpp
 */

#include "UnirseAPartida.h"

#include <sstream>

#include "../../Utiles/Excepcion.h"

destinatarios_posibles UnirseAPartida::destinatarios =
		destinatarios_posibles::servidor;

UnirseAPartida::UnirseAPartida(const std::string& comando_completo)
		throw (std::exception) :
		Mensaje(comando_completo, UnirseAPartida::destinatarios), id_partida(
		ID_PARTIDA_INVALIDO) {

	std::istringstream mensaje_a_parsear(comando_completo);

	std::string comando;
	mensaje_a_parsear >> comando;
	mensaje_a_parsear >> this->id_partida;

	if (!cantidadArgumentosRecibidosCorrecta(mensaje_a_parsear))
		throw Excepcion(
				"Cantidad de Argumentos recibidos en Comando UNIRSE_A_PARTIDA no válido.");

	if (comando != UNIRSE_A_PARTIDA)
		throw Excepcion("Comando UNIRSE_A_PARTIDA no válido.");

	if (id_partida < ID_PARTIDA_MINIMO)
		throw Excepcion("ID PARTIDA en UNIRSE_A_PARTIDA no válido.");
}

UnirseAPartida::UnirseAPartida(int id_partida) :
		id_partida(id_partida) {

	if (id_partida < ID_PARTIDA_MINIMO)
		throw Excepcion("ID PARTIDA en UNIRSE_A_PARTIDA no válido.");

	this->receptor = getDestinatariosSegunTipoMensaje();
	this->mensaje = serializar();
}

std::string UnirseAPartida::serializar() {
	std::ostringstream unirse_a_partida;
	unirse_a_partida << UNIRSE_A_PARTIDA << DELIMITADOR_CAMPOS << getIdPartida()
			<< DELIMITADOR_REGISTROS;
	return unirse_a_partida.str();
}

int UnirseAPartida::getIdPartida() const {
	return id_partida;
}

destinatarios_posibles UnirseAPartida::getDestinatariosSegunTipoMensaje() const {
	return destinatarios;
}

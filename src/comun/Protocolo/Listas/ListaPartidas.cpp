/*
 * ListaPartidas.cpp
 */

#include "ListaPartidas.h"

#include <sstream>

#include "../../Utiles/Excepcion.h"
#include "../Protocolo.h"

destinatarios_posibles ListaPartidas::destinatarios =
		destinatarios_posibles::no_es_necesario;

ListaPartidas::ListaPartidas(const std::string & comando_completo)
		throw (std::exception) :
		Mensaje(comando_completo, ListaPartidas::destinatarios) {

	std::istringstream mensaje_a_parsear(comando_completo);
	std::string comando;
	mensaje_a_parsear >> comando;

	if (comando != LISTA_PARTIDAS_NO_INICIADAS)
		throw Excepcion("Comando LISTA_PARTIDAS_NO_INICIADAS no válido.");

	cargarPartidas(mensaje_a_parsear);
}

void ListaPartidas::cargarPartidas(std::istringstream & mensaje_a_parsear) {

	while (!mensaje_a_parsear.eof()) {
		int id_partida;
		int cantidad_de_jugadores_unidos;
		int cantidad_de_jugadores_esperados;
		int id_escenario;
		std::string nombre_escenario;

		mensaje_a_parsear >> id_partida;
		mensaje_a_parsear >> cantidad_de_jugadores_unidos;
		mensaje_a_parsear >> cantidad_de_jugadores_esperados;
		mensaje_a_parsear >> id_escenario;
		mensaje_a_parsear >> nombre_escenario;
		this->partidas[id_partida] = nombre_escenario;
	}
}

ListaPartidas::ListaPartidas(int id_manejador_cliente,
		const std::string & lista_de_partidas_concatenadas) :
		id_manejador_cliente(id_manejador_cliente), lista_de_partidas_concatenadas(
				lista_de_partidas_concatenadas) {
	std::istringstream mensaje_a_parsear(lista_de_partidas_concatenadas);

	cargarPartidas(mensaje_a_parsear);
	this->receptor = getDestinatariosSegunTipoMensaje();
	this->mensaje = serializar();

}

std::map<int, std::string> ListaPartidas::getPartidas() {
	return partidas;
}

std::string ListaPartidas::serializar() const {
	std::ostringstream oss("");
	oss << LISTA_PARTIDAS_NO_INICIADAS << getListaDePartidasConcatenadas()
			<< DELIMITADOR_REGISTROS;
	return oss.str();
}

destinatarios_posibles ListaPartidas::getDestinatariosSegunTipoMensaje() const {
	return destinatarios;
}

const std::string& ListaPartidas::getListaDePartidasConcatenadas() const {
	return lista_de_partidas_concatenadas;
}

ListaPartidas::~ListaPartidas() {
}


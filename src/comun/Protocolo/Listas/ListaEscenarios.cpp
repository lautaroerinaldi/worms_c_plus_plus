/*
 * ListaEscenarios.cpp
 */

#include "ListaEscenarios.h"

#include <sstream>

#include "../../Utiles/Excepcion.h"
#include "../Protocolo.h"

destinatarios_posibles ListaEscenarios::destinatarios =
		destinatarios_posibles::no_es_necesario;

ListaEscenarios::ListaEscenarios(const std::string & comando_completo)
		throw (std::exception) :
		Mensaje(comando_completo, ListaEscenarios::destinatarios) {

	std::istringstream mensaje_a_parsear(comando_completo);
	std::string comando;
	mensaje_a_parsear >> comando;

	if (comando != LISTA_ESCENARIOS)
		throw Excepcion("Comando LISTA_ESCENARIOS no válido.");

	cargarEscenarios(mensaje_a_parsear);
}

ListaEscenarios::ListaEscenarios(int id_manejador_cliente,
		const std::string & lista_de_escenarios_concatenadas) :
		id_manejador_cliente(id_manejador_cliente), lista_de_escenarios_concatenadas(
				lista_de_escenarios_concatenadas) {

	std::istringstream mensaje_a_parsear(lista_de_escenarios_concatenadas);

	cargarEscenarios(mensaje_a_parsear);
	this->receptor = getDestinatariosSegunTipoMensaje();
	this->mensaje = serializar();
}

void ListaEscenarios::cargarEscenarios(std::istringstream & mensaje_a_parsear) {
	while (!mensaje_a_parsear.eof()) {
		int id_escenario;
		std::string nombre_escenario;
		mensaje_a_parsear >> id_escenario;
		mensaje_a_parsear >> nombre_escenario;
		this->escenarios[id_escenario] = nombre_escenario;
	}
}

std::map<int, std::string> ListaEscenarios::getEscenarios() {
	return this->escenarios;
}

std::string ListaEscenarios::serializar() const {
	std::ostringstream oss("");
	oss << LISTA_ESCENARIOS << getListaDeEscenariosConcatenados() << DELIMITADOR_REGISTROS;
	return oss.str();
}

destinatarios_posibles ListaEscenarios::getDestinatariosSegunTipoMensaje() const {
	return destinatarios;
}

const std::string& ListaEscenarios::getListaDeEscenariosConcatenados() const {
	return lista_de_escenarios_concatenadas;
}

ListaEscenarios::~ListaEscenarios() {
}


/*
 * ListaEscenarios.h
 */

#ifndef SRC_COMUN_PROTOCOLO_LISTAS_LISTAESCENARIOS_H_
#define SRC_COMUN_PROTOCOLO_LISTAS_LISTAESCENARIOS_H_

#include <map>
#include <string>

#include "../../DefinicionesPrivadas.h"
#include "../Mensaje.h"

class ListaEscenarios: public Mensaje {
	static destinatarios_posibles destinatarios;

	int id_manejador_cliente;
	std::map<int, std::string> escenarios;
	std::string lista_de_escenarios_concatenadas;
	const std::string& getListaDeEscenariosConcatenados() const;

	void cargarEscenarios(std::istringstream & mensaje_a_parsear);


public:
	ListaEscenarios(const std::string & comando_completo) throw (std::exception);

	ListaEscenarios(int id_manejador_cliente,
			const std::string & lista_de_escenarios_concatenadas);

	std::map<int, std::string> getEscenarios();

	std::string serializar() const;
	destinatarios_posibles getDestinatariosSegunTipoMensaje() const;

	virtual ~ListaEscenarios();
};

#endif /* SRC_COMUN_PROTOCOLO_LISTAS_LISTAESCENARIOS_H_ */

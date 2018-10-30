/*
 * ListaPartidas.h
 */

#ifndef SRC_COMUN_PROTOCOLO_LISTAS_LISTAPARTIDAS_H_
#define SRC_COMUN_PROTOCOLO_LISTAS_LISTAPARTIDAS_H_

#include <map>
#include <string>

#include "../../DefinicionesPrivadas.h"
#include "../Mensaje.h"

class ListaPartidas: public Mensaje {
	static destinatarios_posibles destinatarios;

	int id_manejador_cliente;

	// id_partida - nombre_escenario
	std::map<int, std::string> partidas;

	std::string lista_de_partidas_concatenadas;
	const std::string& getListaDePartidasConcatenadas() const;

	void cargarPartidas(std::istringstream & mensaje_a_parsear);

public:
	ListaPartidas(const std::string & comando_completo) throw (std::exception);

	ListaPartidas(int id_manejador_cliente,
			const std::string & lista_de_partidas_concatenadas);

	std::string serializar() const;
	destinatarios_posibles getDestinatariosSegunTipoMensaje() const;

	std::map<int, std::string> getPartidas();

	virtual ~ListaPartidas();
};

#endif /* SRC_COMUN_PROTOCOLO_LISTAS_LISTAPARTIDAS_H_ */

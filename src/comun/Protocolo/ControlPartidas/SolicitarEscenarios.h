/*
 * SolicitarEscenarios.h
 */

#ifndef SRC_COMUN_PROTOCOLO_CONTROLPARTIDAS_SOLICITARESCENARIOS_H_
#define SRC_COMUN_PROTOCOLO_CONTROLPARTIDAS_SOLICITARESCENARIOS_H_

#include "../Mensaje.h"

#include <exception>
#include <string>

class SolicitarEscenarios: public Mensaje {
	static destinatarios_posibles destinatarios;

public:
	SolicitarEscenarios();
	SolicitarEscenarios(const std::string & comando_completo)
			throw (std::exception);

	std::string serializar();
	destinatarios_posibles getDestinatariosSegunTipoMensaje() const;

	~SolicitarEscenarios();
};

#endif /* SRC_COMUN_PROTOCOLO_CONTROLPARTIDAS_SOLICITARESCENARIOS_H_ */

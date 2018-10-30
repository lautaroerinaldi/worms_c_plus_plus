/*
 * FinalizarEscenario.h
 */

#ifndef SRC_COMUN_PROTOCOLO_CONTROLMAQUINADEESTADOS_FINALIZARESCENARIO_H_
#define SRC_COMUN_PROTOCOLO_CONTROLMAQUINADEESTADOS_FINALIZARESCENARIO_H_

#include "../Mensaje.h"

class FinalizarEscenario: public Mensaje {
	static destinatarios_posibles destinatarios;
public:
	FinalizarEscenario();
	FinalizarEscenario(const std::string & comando_completo)
			throw (std::exception);
	std::string serializar();
	destinatarios_posibles getDestinatariosSegunTipoMensaje() const;
};

#endif /* SRC_COMUN_PROTOCOLO_CONTROLMAQUINADEESTADOS_FINALIZARESCENARIO_H_ */

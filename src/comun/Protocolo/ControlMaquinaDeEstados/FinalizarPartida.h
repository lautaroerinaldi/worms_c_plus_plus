/*
 * FinalizarPartida.h
 */

#ifndef SRC_COMUN_PROTOCOLO_CONTROLMAQUINADEESTADOS_FINALIZARPARTIDA_H_
#define SRC_COMUN_PROTOCOLO_CONTROLMAQUINADEESTADOS_FINALIZARPARTIDA_H_

#include "../Mensaje.h"

class FinalizarPartida: public Mensaje {
	static destinatarios_posibles destinatarios;
public:
	FinalizarPartida();
	FinalizarPartida(const std::string & comando_completo)
			throw (std::exception);
	std::string serializar();
	destinatarios_posibles getDestinatariosSegunTipoMensaje() const;
};

#endif /* SRC_COMUN_PROTOCOLO_CONTROLMAQUINADEESTADOS_FINALIZARPARTIDA_H_ */

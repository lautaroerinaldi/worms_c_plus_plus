/*
 * IniciarPartida.h
 */

#ifndef SRC_COMUN_PROTOCOLO_CONTROLMAQUINADEESTADOS_INICIARPARTIDA_H_
#define SRC_COMUN_PROTOCOLO_CONTROLMAQUINADEESTADOS_INICIARPARTIDA_H_

#include "../Mensaje.h"

class IniciarPartida: public Mensaje {
	static destinatarios_posibles destinatarios;

public:
	IniciarPartida();
	IniciarPartida(const std::string & comando_completo) throw (std::exception);
	std::string serializar();
	destinatarios_posibles getDestinatariosSegunTipoMensaje() const;
};

#endif /* SRC_COMUN_PROTOCOLO_CONTROLMAQUINADEESTADOS_INICIARPARTIDA_H_ */

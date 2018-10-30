/*
 * SolicitarPartidasNoIniciadas.h
 */

#ifndef SRC_COMUN_PROTOCOLO_CONTROLPARTIDAS_SOLICITARPARTIDASNOINICIADAS_H_
#define SRC_COMUN_PROTOCOLO_CONTROLPARTIDAS_SOLICITARPARTIDASNOINICIADAS_H_

#include "../Mensaje.h"

#include <exception>
#include <string>

class SolicitarPartidasNoIniciadas: public Mensaje {
	static destinatarios_posibles destinatarios;

public:
	SolicitarPartidasNoIniciadas();
	SolicitarPartidasNoIniciadas(const std::string & comando_completo)
			throw (std::exception);

	std::string serializar();
	destinatarios_posibles getDestinatariosSegunTipoMensaje() const;

	~SolicitarPartidasNoIniciadas();
};

#endif /* SRC_COMUN_PROTOCOLO_CONTROLPARTIDAS_SOLICITARPARTIDASNOINICIADAS_H_ */

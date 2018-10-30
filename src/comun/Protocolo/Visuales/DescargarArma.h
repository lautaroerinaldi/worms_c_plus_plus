/*
 * DescargarArma.h
 */

#ifndef SRC_COMUN_PROTOCOLO_VISUALES_DESCARGARARMA_H_
#define SRC_COMUN_PROTOCOLO_VISUALES_DESCARGARARMA_H_

#include "../Mensaje.h"

#include <exception>
#include <string>

class DescargarArma: public Mensaje {
	static destinatarios_posibles destinatarios;

public:
	DescargarArma();
	DescargarArma(const std::string& comando_completo) throw (std::exception);
	virtual ~DescargarArma();
	destinatarios_posibles getDestinatariosSegunTipoMensaje() const;
	std::string serializar() const;
};

#endif /* SRC_COMUN_PROTOCOLO_VISUALES_DESCARGARARMA_H_ */

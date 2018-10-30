/*
 * Atacar.h
 */

#ifndef SRC_COMUN_PROTOCOLO_ARMAS_ATACAR_H_
#define SRC_COMUN_PROTOCOLO_ARMAS_ATACAR_H_

#include "../Mensaje.h"

#include <exception>
#include <string>

class Atacar: public Mensaje {
	static destinatarios_posibles destinatarios;

public:
	Atacar();
	Atacar(const std::string& comando_completo) throw (std::exception);

	destinatarios_posibles getDestinatariosSegunTipoMensaje() const;
	std::string serializar() const;

	virtual ~Atacar();
};

#endif /* SRC_COMUN_PROTOCOLO_ARMAS_ATACAR_H_ */

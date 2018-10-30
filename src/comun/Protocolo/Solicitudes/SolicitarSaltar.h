/*
 * SolicitarSaltar.h
 */

#ifndef SRC_COMUN_PROTOCOLO_SOLICITUDES_SOLICITARSALTAR_H_
#define SRC_COMUN_PROTOCOLO_SOLICITUDES_SOLICITARSALTAR_H_

#include "SolicitarMover.h"

#include <exception>
#include <string>

class SolicitarSaltar: public SolicitarMover {
protected:
	virtual std::string getComando() const;
public:
	SolicitarSaltar(const std::string & comando_completo) throw (std::exception);
	SolicitarSaltar(int direccion) throw (std::exception);
	virtual ~SolicitarSaltar();
};

#endif /* SRC_COMUN_PROTOCOLO_SOLICITUDES_SOLICITARSALTAR_H_ */

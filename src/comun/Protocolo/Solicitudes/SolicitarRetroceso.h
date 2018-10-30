/*
 * SolicitarRetroceso.h
 */

#ifndef SRC_COMUN_PROTOCOLO_SOLICITUDES_SOLICITARRETROCESO_H_
#define SRC_COMUN_PROTOCOLO_SOLICITUDES_SOLICITARRETROCESO_H_

#include "SolicitarMover.h"

#include <exception>
#include <string>

class SolicitarRetroceso: public SolicitarMover {
protected:
	virtual std::string getComando() const;
public:
	SolicitarRetroceso(const std::string & comando_completo)
			throw (std::exception);
	SolicitarRetroceso(int direccion) throw (std::exception);
	virtual ~SolicitarRetroceso();
};

#endif /* SRC_COMUN_PROTOCOLO_SOLICITUDES_SOLICITARRETROCESO_H_ */

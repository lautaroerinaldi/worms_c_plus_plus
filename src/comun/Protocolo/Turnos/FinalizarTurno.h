/*
 * FinalizarTurno.h
 */

#ifndef SRC_COMUN_PROTOCOLO_TURNOS_FINALIZARTURNO_H_
#define SRC_COMUN_PROTOCOLO_TURNOS_FINALIZARTURNO_H_

#include "../Mensaje.h"

#include <exception>
#include <string>

class FinalizarTurno: public Mensaje {
	static destinatarios_posibles destinatarios;

public:
	FinalizarTurno();
	FinalizarTurno(const std::string & comando_completo) throw (std::exception);

	virtual std::string serializar() const;
	destinatarios_posibles getDestinatariosSegunTipoMensaje() const;

	virtual ~FinalizarTurno();
};

#endif /* SRC_COMUN_PROTOCOLO_TURNOS_FINALIZARTURNO_H_ */

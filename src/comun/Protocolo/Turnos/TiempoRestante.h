/*
 * TiempoRestante.h
 */

#ifndef SRC_COMUN_PROTOCOLO_TURNOS_TIEMPORESTANTE_H_
#define SRC_COMUN_PROTOCOLO_TURNOS_TIEMPORESTANTE_H_

#include "../Mensaje.h"

#include <exception>
#include <string>

class TiempoRestante: public Mensaje {
	static destinatarios_posibles destinatarios;

	int tiempo_restante;

public:
	TiempoRestante(int tiempo_restante) throw (std::exception);
	TiempoRestante(const std::string & comando_completo) throw (std::exception);

	int getTiempoRestante() const;

	std::string serializar() const;
	destinatarios_posibles getDestinatariosSegunTipoMensaje() const;

	virtual ~TiempoRestante();
};

#endif /* SRC_COMUN_PROTOCOLO_TURNOS_TIEMPORESTANTE_H_ */

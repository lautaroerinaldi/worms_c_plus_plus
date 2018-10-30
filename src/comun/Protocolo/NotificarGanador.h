/*
 * NotificarGanador.h
 */

#ifndef SRC_COMUN_PROTOCOLO_NOTIFICARGANADOR_H_
#define SRC_COMUN_PROTOCOLO_NOTIFICARGANADOR_H_

#include "Mensaje.h"

#include <exception>
#include <string>

class NotificarGanador: public Mensaje {
	static destinatarios_posibles destinatarios;

	int id_jugador_ganador;
public:
	NotificarGanador(const std::string & comando_completo)
			throw (std::exception);
	NotificarGanador(int id_jugador_ganador);

	virtual std::string serializar() const;
	destinatarios_posibles getDestinatariosSegunTipoMensaje() const;

	int getIdJugadorGanador() const;

	virtual ~NotificarGanador();
};

#endif /* SRC_COMUN_PROTOCOLO_NOTIFICARGANADOR_H_ */

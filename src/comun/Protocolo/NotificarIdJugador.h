/*
 * NotificarIdJugador.h
 */

#ifndef SRC_COMUN_PROTOCOLO_NOTIFICARIDJUGADOR_H_
#define SRC_COMUN_PROTOCOLO_NOTIFICARIDJUGADOR_H_

#include "Mensaje.h"

class NotificarIdJugador:public Mensaje {
	static destinatarios_posibles destinatarios;

	int id_jugador;
public:
	NotificarIdJugador(int id_jugador);
	NotificarIdJugador(const std::string & comando_completo);

	std::string serializar() const;
	destinatarios_posibles getDestinatariosSegunTipoMensaje() const;

	~NotificarIdJugador();
	int getIdJugador() const;
};

#endif /* SRC_COMUN_PROTOCOLO_NOTIFICARIDJUGADOR_H_ */

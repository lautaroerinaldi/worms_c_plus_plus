/*
 * NotificarIdPartida.h
 */

#ifndef SRC_COMUN_PROTOCOLO_NOTIFICARIDPARTIDA_H_
#define SRC_COMUN_PROTOCOLO_NOTIFICARIDPARTIDA_H_

#include "Mensaje.h"

class NotificarIdPartida: public Mensaje {
	static destinatarios_posibles destinatarios;

	int id_partida;
public:
	NotificarIdPartida(int id_partida);
	NotificarIdPartida(const std::string & comando_completo);

	std::string serializar() const;
	destinatarios_posibles getDestinatariosSegunTipoMensaje() const;

	~NotificarIdPartida();
	int getIdPartida() const;
};

#endif /* SRC_COMUN_PROTOCOLO_NOTIFICARIDPARTIDA_H_ */

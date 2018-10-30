/*
 * UnirseAPartida.h
 */

#ifndef COMUN_PROTOCOLO_UNIRSEAPARTIDA_H_
#define COMUN_PROTOCOLO_UNIRSEAPARTIDA_H_

#include "../Mensaje.h"
#include "../Protocolo.h"

#include <exception>
#include <string>

class UnirseAPartida: public Mensaje {
	static destinatarios_posibles destinatarios;
	int id_partida;

public:
	UnirseAPartida(const std::string & comando_completo) throw (std::exception);
	UnirseAPartida(int id_partida);
	std::string serializar();
	destinatarios_posibles getDestinatariosSegunTipoMensaje() const;
	int getIdPartida() const;
};

#endif /* COMUN_PROTOCOLO_UNIRSEAPARTIDA_H_ */

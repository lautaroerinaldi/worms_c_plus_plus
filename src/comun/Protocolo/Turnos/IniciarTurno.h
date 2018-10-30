/*
 * IniciarTurno.h
 */

#ifndef SRC_COMUN_PROTOCOLO_TURNOS_INICIARTURNO_H_
#define SRC_COMUN_PROTOCOLO_TURNOS_INICIARTURNO_H_

#include "../Mensaje.h"

#include <exception>
#include <string>

class IniciarTurno: public Mensaje {
	static destinatarios_posibles destinatarios;

	int id_jugador;
	int id_gusano;
public:
	IniciarTurno(const std::string & comando_completo) throw (std::exception);
	IniciarTurno(int id_jugador, int id_gusano);

	virtual std::string serializar() const;
	destinatarios_posibles getDestinatariosSegunTipoMensaje() const;

	int getIdJugador() const;
	int getIdGusano() const;

	virtual ~IniciarTurno();
};

#endif /* SRC_COMUN_PROTOCOLO_TURNOS_INICIARTURNO_H_ */

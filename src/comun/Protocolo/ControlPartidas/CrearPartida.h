/*
 * CrearPartida.h
 */

#ifndef COMUN_PROTOCOLO_CREARPARTIDA_H_
#define COMUN_PROTOCOLO_CREARPARTIDA_H_

#include "../Mensaje.h"
#include "../Protocolo.h"

#include <exception>
#include <string>

class CrearPartida: public Mensaje {
	static destinatarios_posibles destinatarios;

	unsigned int id_escenario;
	unsigned int cantidad_jugadores_esperados;

public:
	CrearPartida(const std::string & comando_completo) throw (std::exception);
	CrearPartida(unsigned int id_escenario,
			unsigned int cantidad_jugadores_esperados);

	std::string serializar();
	unsigned int getCantidadJugadoresEsperados() const;
	unsigned int getIdEscenario() const;
	destinatarios_posibles getDestinatariosSegunTipoMensaje() const;
};

#endif /* COMUN_PROTOCOLO_CREARPARTIDA_H_ */

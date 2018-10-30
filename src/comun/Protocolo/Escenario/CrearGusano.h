/*
 * CrearGusano.h
 */

#ifndef SRC_COMUN_PROTOCOLO_ESCENARIO_CREARGUSANO_H_
#define SRC_COMUN_PROTOCOLO_ESCENARIO_CREARGUSANO_H_

#include "../Mensaje.h"

class CrearGusano: public Mensaje {
	static destinatarios_posibles destinatarios;

	int id_gusano;
	int id_jugador;
	int vida;
	int x;
	int y;
	int inclinacion;
public:
	CrearGusano(const std::string & comando_completo) throw (std::exception);
	CrearGusano(int id_gusano, int id_jugador, int vida, float x, float y, int inclinacion);
	std::string serializar();
	destinatarios_posibles getDestinatariosSegunTipoMensaje() const;
	int getIdGusano() const;
	int getIdJugador() const;
	int getVida() const;
	int getX() const;
	int getY() const;
	int getInclinacion() const;
};

#endif /* SRC_COMUN_PROTOCOLO_ESCENARIO_CREARGUSANO_H_ */

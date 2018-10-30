/*
 * Teletransportar.h
 */

#ifndef SRC_COMUN_PROTOCOLO_ARMAS_TELETRANSPORTARGUSANO_H_
#define SRC_COMUN_PROTOCOLO_ARMAS_TELETRANSPORTARGUSANO_H_

#include "../Mensaje.h"

#include <exception>
#include <string>

class TeletransportarGusano: public Mensaje {
	static destinatarios_posibles destinatarios;

	float x_modelo;
	float y_modelo;
public:
	TeletransportarGusano(const std::string & comando_completo) throw (std::exception);
	TeletransportarGusano(float x_modelo, float y_modelo);

	virtual std::string serializar() const;
	destinatarios_posibles getDestinatariosSegunTipoMensaje() const;

	int getXVista() const;
	int getYVista() const;

	float getYModelo() const;
	float getXModelo() const;

	virtual ~TeletransportarGusano();
};

#endif /* SRC_COMUN_PROTOCOLO_ARMAS_TELETRANSPORTARGUSANO_H_ */

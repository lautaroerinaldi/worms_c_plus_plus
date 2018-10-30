/*
 * ImpactarBala.h
 */

#ifndef SRC_COMUN_PROTOCOLO_BALAS_IMPACTARBALA_H_
#define SRC_COMUN_PROTOCOLO_BALAS_IMPACTARBALA_H_

#include "../Mensaje.h"

#include <exception>
#include <string>

class ImpactarBala: public Mensaje {
	static destinatarios_posibles destinatarios;

	int id_bala;
	float x_modelo;
	float y_modelo;
	float radio_modelo;

	bool direccionValida(int direccion);
public:
	ImpactarBala(const std::string & comando_completo) throw (std::exception);
	ImpactarBala(int id_bala, float x_modelo, float y_modelo,
			float radio_modelo);

	virtual std::string serializar() const;
	destinatarios_posibles getDestinatariosSegunTipoMensaje() const;

	int getIdBala() const;

	float getXModelo() const;
	float getYModelo() const;

	int getXVista() const;
	int getYVista() const;

	float getRadioModelo() const;
	int getRadioVista() const;

	virtual ~ImpactarBala();
};

#endif /* SRC_COMUN_PROTOCOLO_BALAS_IMPACTARBALA_H_ */

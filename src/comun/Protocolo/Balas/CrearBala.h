/*
 * CrearBala.h
 */

#ifndef SRC_COMUN_PROTOCOLO_BALAS_CREARBALA_H_
#define SRC_COMUN_PROTOCOLO_BALAS_CREARBALA_H_

#include "../Mensaje.h"

#include <exception>
#include <string>

class CrearBala: public Mensaje {
	static destinatarios_posibles destinatarios;

	int id_bala;
	float x_modelo;
	float y_modelo;
	float angulo_en_grados;
	int direccion;
	int tipo_arma;

	bool direccionValida(int direccion);
	bool tipoArmaValida(int tipo_arma);
public:
	CrearBala(const std::string & comando_completo) throw (std::exception);
	CrearBala(int id_bala, float x_modelo, float y_modelo, float angulo_en_grados,
			int direccion, int tipo_arma) throw (std::exception);

	virtual std::string serializar() const;
	destinatarios_posibles getDestinatariosSegunTipoMensaje() const;

	int getAnguloEnGrados() const;
	int getDireccion() const;
	int getIdBala() const;

	float getXModelo() const;
	float getYModelo() const;

	int getXVista() const;
	int getYVista() const;

	int getTipoArma() const;

	virtual ~CrearBala();
};

#endif /* SRC_COMUN_PROTOCOLO_BALAS_CREARBALA_H_ */

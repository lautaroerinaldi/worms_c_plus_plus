/*
 * MoverBala.h
 */

#ifndef SRC_COMUN_PROTOCOLO_BALAS_MOVERBALA_H_
#define SRC_COMUN_PROTOCOLO_BALAS_MOVERBALA_H_

#include <string>
#include "../Mensaje.h"

class MoverBala: public Mensaje {
	static destinatarios_posibles destinatarios;

	int id_bala;
	float x_modelo;
	float y_modelo;
	float angulo_en_grados;
	int direccion;

	bool direccionValida(int direccion);
public:
	MoverBala(const std::string & comando_completo) throw (std::exception);
	MoverBala(int id_bala, float x_modelo, float y_modelo, float angulo_en_grados,
			int direccion) throw (std::exception);

	virtual std::string serializar() const;
	destinatarios_posibles getDestinatariosSegunTipoMensaje() const;

	int getAnguloEnGrados() const;
	int getDireccion() const;
	int getIdBala() const;

	float getXModelo() const;
	float getYModelo() const;

	int getXVista() const;
	int getYVista() const;

	virtual ~MoverBala();
};

#endif /* SRC_COMUN_PROTOCOLO_BALAS_MOVERBALA_H_ */

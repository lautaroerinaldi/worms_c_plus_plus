/*
 * Volar.h
 */

#ifndef SRC_COMUN_PROTOCOLO_MOVIMIENTOSGUSANOS_VOLARGUSANO_H_
#define SRC_COMUN_PROTOCOLO_MOVIMIENTOSGUSANOS_VOLARGUSANO_H_

#include "../Mensaje.h"

#include <exception>
#include <string>

class VolarGusano: public Mensaje {
	static destinatarios_posibles destinatarios;

	int id_gusano;
	float x_modelo;
	float y_modelo;
	int angulo_en_grados;
public:
	VolarGusano();

	VolarGusano(const std::string & comando_completo) throw (std::exception);
	VolarGusano(int id_gusano, float x_modelo, float y_modelo, int angulo_en_grados);

	virtual std::string serializar() const;
	destinatarios_posibles getDestinatariosSegunTipoMensaje() const;

	int getIdGusano() const;
	int getAnguloEnGrados() const;

	float getXModelo() const;
	float getYModelo() const;

	int getXVista() const;
	int getYVista() const;

	virtual ~VolarGusano();
};

#endif /* SRC_COMUN_PROTOCOLO_MOVIMIENTOSGUSANOS_VOLARGUSANO_H_ */

/*
 * InformarViento.h
 */

#ifndef SRC_COMUN_PROTOCOLO_INFORMARVIENTO_H_
#define SRC_COMUN_PROTOCOLO_INFORMARVIENTO_H_

#include "Mensaje.h"

#include "../Codigos.h"

#include <exception>
#include <string>

class InformarViento: public Mensaje {
	static destinatarios_posibles destinatarios;

	float magnitud_viento_en_metros_por_segundo_sin_signo;
	int direccion;

	bool direccionValida(int direccion);
public:
	InformarViento(float magnitud_viento_en_metros_por_segundo_sin_signo,
			int direccion) throw (std::exception);

	InformarViento(const std::string & comando_completo) throw (std::exception);

	int getDireccion() const;
	int getMagnitudVientoEnCentimetrosPorSegundo() const;

	std::string serializar() const;
	destinatarios_posibles getDestinatariosSegunTipoMensaje() const;

	virtual ~InformarViento();
};

#endif /* SRC_COMUN_PROTOCOLO_INFORMARVIENTO_H_ */

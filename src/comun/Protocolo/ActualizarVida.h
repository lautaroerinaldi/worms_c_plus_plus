/*
 * ActualizarVida.h
 */

#ifndef SRC_COMUN_PROTOCOLO_ACTUALIZARVIDA_H_
#define SRC_COMUN_PROTOCOLO_ACTUALIZARVIDA_H_

#include "Mensaje.h"

#include <exception>
#include <string>

class ActualizarVida: public Mensaje {
	static destinatarios_posibles destinatarios;

	int id_gusano;
	int vida;
	int inclinacion;

	bool inclinacionValida(int inclinacion);
public:
	ActualizarVida(int id_gusano, int vida, int inclinacion)
			throw (std::exception);
	ActualizarVida(const std::string & comando_completo) throw (std::exception);

	int getIdGusano() const;
	int getInclinacion() const;
	int getVida() const;

	std::string serializar() const;
	destinatarios_posibles getDestinatariosSegunTipoMensaje() const;

	virtual ~ActualizarVida();
};

#endif /* SRC_COMUN_PROTOCOLO_ACTUALIZARVIDA_H_ */

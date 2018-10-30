/*
 * Direccionar.h
 */

#ifndef SRC_COMUN_PROTOCOLO_VISUALES_DIRECCIONARGUSANO_H_
#define SRC_COMUN_PROTOCOLO_VISUALES_DIRECCIONARGUSANO_H_

#include "../Mensaje.h"

#include <exception>
#include <string>

class DireccionarGusano: public Mensaje {
	static destinatarios_posibles destinatarios;

	int direccion;

	bool direccionValida(int direccion);
public:
	DireccionarGusano(const std::string & comando_completo) throw (std::exception);
	DireccionarGusano(int direccion)throw (std::exception);

	int getDireccion() const;

	std::string serializar();
	destinatarios_posibles getDestinatariosSegunTipoMensaje() const;

	virtual ~DireccionarGusano();
};

#endif /* SRC_COMUN_PROTOCOLO_VISUALES_DIRECCIONARGUSANO_H_ */

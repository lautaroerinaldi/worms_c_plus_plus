/*
 * SolicitarMover.h
 */

#ifndef COMUN_PROTOCOLO_SOLICITARMOVER_H_
#define COMUN_PROTOCOLO_SOLICITARMOVER_H_

#include "../Mensaje.h"

#include <exception>
#include <string>

class SolicitarMover: public Mensaje {
protected:
	static destinatarios_posibles destinatarios;

	int direccion;

	bool direccionValida(int direccion);
	bool comandoCorrecto(const std::string & comando) const;
	virtual std::string getComando() const;

public:
	SolicitarMover(const std::string & comando_completo) throw (std::exception);
	SolicitarMover(int direccion) throw (std::exception);

	int getDireccion() const;

	virtual std::string serializar() const;
	destinatarios_posibles getDestinatariosSegunTipoMensaje() const;

	virtual ~SolicitarMover();
};

#endif /* COMUN_PROTOCOLO_SOLICITARMOVER_H_ */

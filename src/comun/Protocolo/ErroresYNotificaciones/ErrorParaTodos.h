/*
 * ErrorParaTodos.h
 */

#ifndef COMUN_PROTOCOLO_ERRORPARATODOS_H_
#define COMUN_PROTOCOLO_ERRORPARATODOS_H_

#include "../Mensaje.h"
#include "../../Codigos.h"

#include <exception>
#include <string>

class ErrorParaTodos: public Mensaje {
	static destinatarios_posibles destinatarios;

	int tipo_de_error;
	std::string mensaje_de_error;

	bool tipoErrorValido(int tipo_de_error);
public:
	ErrorParaTodos(int tipo_de_error, const std::string & mensaje_de_error)
			throw (std::exception);
	ErrorParaTodos(const std::string & comando_completo) throw (std::exception);

	const std::string& getMensajeDeError() const;

	std::string serializar();
	destinatarios_posibles getDestinatariosSegunTipoMensaje() const;

	virtual ~ErrorParaTodos();
	int getTipoDeError() const;
};

#endif /* COMUN_PROTOCOLO_ERRORPARATODOS_H_ */

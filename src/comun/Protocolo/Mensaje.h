/*
 * Mensaje.h
 */

#ifndef COMUN_PROTOCOLO_MENSAJE_H_
#define COMUN_PROTOCOLO_MENSAJE_H_

#include <string>
#include "../DefinicionesPrivadas.h"
#include "Protocolo.h"
#include <sstream>

class Mensaje {
protected:
	int id_emisor;
	std::string mensaje;
	destinatarios_posibles receptor;

	bool cantidadArgumentosRecibidosCorrecta(
			const std::istringstream & origen_del_parseo);
public:
	Mensaje();
	Mensaje(int id_emisor, const std::string & mensaje);
	Mensaje(const std::string & mensaje, destinatarios_posibles receptor);


	int getEmisor();
	std::string getMensaje();
	destinatarios_posibles getReceptor() const;

	virtual std::string serializar() const;
	virtual destinatarios_posibles getDestinatariosSegunTipoMensaje() const;

	// COPIAR Mensaje
	Mensaje(const Mensaje& otro);
	Mensaje& operator=(const Mensaje& otro) = delete;

	// MOVER Mensaje
	Mensaje(Mensaje&& otro);
	Mensaje& operator=(Mensaje&& otro) = delete;

	virtual ~Mensaje();
};

#endif /* COMUN_PROTOCOLO_MENSAJE_H_ */

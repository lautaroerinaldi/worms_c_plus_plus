/*
 * UsuarioAnonimo.h
 */

#ifndef SRC_COMUN_USUARIOANONIMO_H_
#define SRC_COMUN_USUARIOANONIMO_H_

#include <string>

#include "Protocolo/ControlPartidas/CrearPartida.h"
#include "Protocolo/ControlPartidas/UnirseAPartida.h"

class UsuarioAnonimo {
	virtual void enviarMensaje(const Mensaje & mensaje) = 0;
	virtual std::string recibirMensaje() = 0;
public:
	UsuarioAnonimo();

	void crearYUnirseAPartida(const CrearPartida & cp);

	void unirseAPartida(const UnirseAPartida & up);

	void listarPartidasNoIniciadas();

	void listarEscenarios();

	virtual void apagar() = 0;

	virtual ~UsuarioAnonimo();

	// COPIAR UsuarioAnonimo
	UsuarioAnonimo(const UsuarioAnonimo& otro) = delete;
	UsuarioAnonimo& operator=(const UsuarioAnonimo& otro) = delete;

	// MOVER UsuarioAnonimo
	UsuarioAnonimo(UsuarioAnonimo&& otro) = delete;
	UsuarioAnonimo& operator=(UsuarioAnonimo&& otro) = delete;
};

#endif /* SRC_COMUN_USUARIOANONIMO_H_ */

/*
 * Correo.h
 */

#ifndef SERVIDOR_CORREO_CORREO_H_
#define SERVIDOR_CORREO_CORREO_H_

#include <list>

#include "../comun/Buzon.h"
#include "../comun/Protocolo/Mensaje.h"
#include "CarteroEmisorDelServer.h"
#include "ManejadorDeCliente.h"

class Correo {
	Buzon<Mensaje> buzon_entrada;
	Buzon<Mensaje> buzon_salida;
	std::list<ManejadorDeCliente*> & destinatarios;
	CarteroEmisorDelServer cartero;

public:
	explicit Correo(std::list<ManejadorDeCliente*> & destinatarios);
	~Correo();

	// COPIAR Correo
	Correo(const Correo& otro) = delete;
	Correo& operator=(const Correo& otro) = delete;

	// MOVER Correo
	Correo(Correo&& otro) = delete;
	Correo& operator=(Correo&& otro) = delete;

	Buzon<Mensaje>& getBuzonEntrada();
	Buzon<Mensaje>& getBuzonSalida();
};

#endif /* SERVIDOR_CORREO_CORREO_H_ */

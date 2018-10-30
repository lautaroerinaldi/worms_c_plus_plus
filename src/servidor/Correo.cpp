/*
 * Correo.cpp
 */

#include "Correo.h"


Buzon<Mensaje>& Correo::getBuzonEntrada() {
	return buzon_entrada;
}

Buzon<Mensaje>& Correo::getBuzonSalida() {
	return buzon_salida;
}

Correo::Correo(std::list<ManejadorDeCliente*> & destinatarios) :
		destinatarios(destinatarios), cartero(buzon_salida, destinatarios) {

}

Correo::~Correo() {
	cartero.detener();
	cartero.join();
}

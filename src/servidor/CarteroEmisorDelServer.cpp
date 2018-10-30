/*
 * CarteroEmisorDelServer.cpp
 */

#include "CarteroEmisorDelServer.h"

#include <unistd.h>

#include "../comun/DefinicionesPrivadas.h"

CarteroEmisorDelServer::CarteroEmisorDelServer(Buzon<Mensaje> & buzon,
		std::list<ManejadorDeCliente*> & destinatarios) :
		activo(true), buzon(buzon), destinatarios(destinatarios) {
	this->start();
}

bool CarteroEmisorDelServer::estaActivo() {
	return (activo);
}

void CarteroEmisorDelServer::detener() {
	if (activo)
		activo = false;
}

void CarteroEmisorDelServer::activar() {
	activo = true;
}

void CarteroEmisorDelServer::notificarAEmisor(int id_emisor,
		Mensaje & mensaje) {
	for (std::list<ManejadorDeCliente*>::iterator it = destinatarios.begin();
			it != destinatarios.end(); ++it) {
		if ((*it)->getIdJugador() == id_emisor) {
			Destinatario * enc = (*it);
			enc->enviarMensaje(mensaje);
		}
	}
}

void CarteroEmisorDelServer::notificarATodos(Mensaje & mensaje) {
	for (std::list<ManejadorDeCliente*>::iterator it = destinatarios.begin();
			it != destinatarios.end(); ++it) {
		Destinatario * enc = (*it);
		enc->enviarMensaje(mensaje);
	}
}

void CarteroEmisorDelServer::run() {
	activar();
	while (activo) {
		while (buzon.hayMensajes()) {
			Mensaje mensaje(buzon.obtenerMensaje());
			switch (mensaje.getReceptor()) {
			case (destinatarios_posibles::todos): {
				notificarATodos(mensaje);
				break;
			}
			case (destinatarios_posibles::emisor): {
				notificarAEmisor(mensaje.getEmisor(), mensaje);
				break;
			}
			case (destinatarios_posibles::servidor): {
				break;
			}
			}
		}
		usleep(TIEMPO_ESPERA_EN_MICROSEGUNDOS / 50);
	}
}

CarteroEmisorDelServer::~CarteroEmisorDelServer() {
}

/*
 * Server.cpp
 */

#include "Servidor.h"

#include <algorithm>
#include <exception>
#include <iostream>

#include "../comun/DefinicionesDePrueba.h"
#include "../comun/Sockets/SocketComunicador.h"

Servidor::Servidor(const std::string & puerto) :
		skt_server(puerto, CANT_CLIENTES_EN_COLA_PRUEBA), vivo(true), admin_partidas(
				AdministradorDePartidas::getInstancia()) {
	this->start();
}

Servidor::~Servidor() {
}

void Servidor::aceptarNuevoCliente() {
	try {
		SocketComunicador socket_nuevo_cliente =
				this->skt_server.aceptarConexion();
		clientes.emplace_back(std::move(socket_nuevo_cliente));
	} catch (std::exception & e) {
		// Se dejan de aceptar clientes nuevos, pero no tiene que cerrarse el SERVER.
		// Los clientes conectados, pueden seguir comunicándose.
		std::cerr << e.what() << std::endl;
		std::cerr << "No se pueden aceptar nuevos clientes." << std::endl;
	}
}

void Servidor::run() {
	while (this->vivo) {
		this->recolectarClientesMuertos();
		this->aceptarNuevoCliente();
	}
}

bool Servidor::clienteMuerto(const ManejadorDeCliente & cliente) {
	return (!cliente.isActivo());
}

void Servidor::joinearClienteMuerto(ManejadorDeCliente & cliente) {
	if (clienteMuerto(cliente))
		cliente.join();
}

void Servidor::apagarClienteVivo(ManejadorDeCliente & cliente) {
	if (!clienteMuerto(cliente))
		cliente.apagar();
}

void Servidor::recolectarClientesMuertos() {
	std::for_each(clientes.begin(), clientes.end(), joinearClienteMuerto);
	clientes.remove_if(clienteMuerto);
}

void Servidor::apagarClientesVivos() {
	std::for_each(clientes.begin(), clientes.end(), apagarClienteVivo);
}

void Servidor::apagar() {
	if (this->vivo) {
		this->vivo = false;
		this->skt_server.cerrarSocket();
		this->apagarClientesVivos();
		admin_partidas.cerrarTodasLasPartidas();
		this->recolectarClientesMuertos();
	}
}

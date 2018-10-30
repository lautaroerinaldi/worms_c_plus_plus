/*
 * SocketAceptador.cpp
 */

#include "SocketAceptador.h"

#include <string>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

bool SocketAceptador::conexionValida() {
	return (this->conexion_valida && this->socket_fd != SOCKET_FD_INVALIDO);
}

void SocketAceptador::cerrarSocket() {
	shutdown(this->socket_fd, SHUT_RDWR);
	close(this->socket_fd);
	this->socket_fd = SOCKET_FD_INVALIDO;
	this->conexion_valida = false;
}

int SocketAceptador::reusarPuerto() {
	// Muy importante, esto debe hacerse antes del BIND.
	int val = 1;
	if (setsockopt(this->socket_fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val))
			< 0) {
		return ERROR_EN_SOCKET;
	} else {
		return OPERACION_SOCKET_OK;
	}
}

SocketAceptador::SocketAceptador(const std::string & puerto,
		int cant_clientes_en_cola) throw (std::exception) :
		puerto(puerto), socket_fd(SOCKET_FD_INVALIDO), res(NULL), conexion_valida(
				false) {
	// cargo el struct con 0s
	memset(&this->encabezado, 0, sizeof(struct addrinfo));

	if (this->crearSocket() == OPERACION_SOCKET_OK) {
		if (this->reusarPuerto() == OPERACION_SOCKET_OK) {
			if (this->enlazarSocket() == OPERACION_SOCKET_OK) {
				if (this->escuchar(cant_clientes_en_cola) == OPERACION_SOCKET_OK) {
					this->conexion_valida = true;
				}
			}
		}
	}
	if (!this->conexion_valida)
		throw Excepcion("No se pudo abrir el socket aceptador.");
}

int SocketAceptador::crearSocket() {
	// SOCK_STREAM significa usar 'tipo' TCP
	this->encabezado.ai_socktype = SOCK_STREAM;
	// AI_PASSIVE Significa Socket destinado a hacer bind
	this->encabezado.ai_flags = AI_PASSIVE;

	// en lista_direcciones se obtiene una lista donde cada nodo es una
	// posible direccion con la cual uno se "podría" conectar
	int rc = getaddrinfo(NULL, this->puerto.c_str(), &this->encabezado,
			&this->res);
	if (rc) {
		//Falla al decodificar SERVICE_NAME con getaddrinfo
		freeaddrinfo(this->res);
		return ERROR_EN_SOCKET;
	}

	if ((this->socket_fd = socket(this->res->ai_family,
			this->encabezado.ai_socktype, this->res->ai_protocol)) < 0) {
		// Falla creando el socket aceptador
		freeaddrinfo(this->res);
		return ERROR_EN_SOCKET;
	} else {
		return OPERACION_SOCKET_OK;
	}
}

// Enlazo la dirección al socket
int SocketAceptador::enlazarSocket() {
	if (bind(this->socket_fd, this->res->ai_addr, this->res->ai_addrlen) < 0) {
		// Falla Bind en socket
		freeaddrinfo(this->res);
		return ERROR_EN_SOCKET;
	} else {
		freeaddrinfo(this->res);
		return OPERACION_SOCKET_OK;
	}
}

int SocketAceptador::escuchar(int cant_clientes_en_cola) {
	if (listen(this->socket_fd, cant_clientes_en_cola) < 0) {
		//Falla Listen en socket
		return ERROR_EN_SOCKET;
	} else {
		return OPERACION_SOCKET_OK;
	}
}

SocketComunicador SocketAceptador::aceptarConexion() throw (std::exception) {
	struct sockaddr addr_cliente;
	socklen_t long_addr_cliente = sizeof(struct sockaddr);
	// Acepto la conexión entrante. La siguiente linea es la BLOQUEANTE
	int socket_com_fd = accept(this->socket_fd, &addr_cliente,
			&long_addr_cliente);
	if (socket_com_fd < 0)
		throw Excepcion("Se cerró el socket aceptador.");
	return std::move(SocketComunicador(socket_com_fd));
}

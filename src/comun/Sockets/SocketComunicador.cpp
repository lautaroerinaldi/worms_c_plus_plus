/*
 * SocketComunicador.cpp
 */

#include "SocketComunicador.h"
#include "../Utiles/Excepcion.h"

#include <string>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

bool SocketComunicador::conexionValida() {
	return (this->conexion_valida && this->socket_fd != SOCKET_FD_INVALIDO);
}

SocketComunicador::SocketComunicador(int socket_fd) :
		puerto(""), ip(""), socket_fd(socket_fd), lista_direcciones(
		NULL), conexion_valida(true) {
}

SocketComunicador::SocketComunicador(const std::string & ip,
		const std::string & puerto) {
	this->conexion_valida = false;
	this->puerto = puerto;
	this->ip = ip;
	this->lista_direcciones = NULL;
	this->socket_fd = SOCKET_FD_INVALIDO;
	if (this->crearSocket() == OPERACION_SOCKET_OK)
		if (this->conectar() == OPERACION_SOCKET_OK) {
			this->conexion_valida = true;
		}
}

bool SocketComunicador::crearSocket() {
	// cargo el struct con 0s
	memset(&this->encabezado, 0, sizeof(struct addrinfo));

	// AF_INET significa usar 'dominio' IPv4 - Protocolo de Internet
	this->encabezado.ai_family = AF_INET;
	// SOCK_STREAM significa usar 'tipo' TCP
	this->encabezado.ai_socktype = SOCK_STREAM;
	// 0 es el 'protocolo'. Puede ponerse de este modo ya que normalmente hay
	// un único protocolo implementado para un determinado 'tipo de socket'
	this->encabezado.ai_protocol = 0;
	this->encabezado.ai_flags = 0;

	if ((this->socket_fd = socket(this->encabezado.ai_family,
			this->encabezado.ai_socktype, this->encabezado.ai_protocol)) < 0) {
		// Falla creando el socket
		return ERROR_EN_SOCKET;
	} else {
		return OPERACION_SOCKET_OK;
	}
}

// pre: espera que ya se haya creado el socket
bool SocketComunicador::conectar() {
	int rc;
	// en lista_direcciones se obtiene una lista donde cada nodo es una
	// posible direccion con la cual uno se "podría" conectar
	rc = getaddrinfo(this->ip.c_str(), this->puerto.c_str(), &this->encabezado,
			&this->lista_direcciones);
	if (rc) {
		//Falla al decodificar HOST_NAME / SERVICE_NAME con getaddrinfo
		freeaddrinfo(lista_direcciones);
		return ERROR_EN_SOCKET;
	}
	rc = connect(this->socket_fd, lista_direcciones->ai_addr,
			lista_direcciones->ai_addrlen);
	if (rc < 0) {
		//Falla al conectar
		freeaddrinfo(lista_direcciones);
		return ERROR_EN_SOCKET;
	}
	freeaddrinfo(lista_direcciones);

	return OPERACION_SOCKET_OK;
}


int SocketComunicador::enviarDatos(const std::string & mensaje) {
	int cantidad_bytes_a_enviar = mensaje.length();
	int cantidad_bytes_enviados = 0;

	while (conexionValida()
			&& (cantidad_bytes_enviados < cantidad_bytes_a_enviar)) {
		int s = send(this->socket_fd, &mensaje[cantidad_bytes_enviados],
				cantidad_bytes_a_enviar - cantidad_bytes_enviados,
				MSG_NOSIGNAL);

		if (s <= 0) {
			this->cerrarSocket();
			return ERROR_EN_SOCKET;
		} else {
			cantidad_bytes_enviados += s;
		}
	}
	return OPERACION_SOCKET_OK;
}

std::string SocketComunicador::recibirDatos(char delimitador)
		throw (std::exception) {
	std::string leidos;
	leidos.clear();
	bool delim_encontrado = false;
	while ((conexionValida()) && (!delim_encontrado)) {
		char c;
		int recibidos = recv(this->socket_fd, &c, 1, MSG_NOSIGNAL);

		if (recibidos <= 0) {
			this->cerrarSocket();
			throw Excepcion("Error en recepcion en Socket Comunicador");
		} else {
			if (c != delimitador)
				leidos += c;
			else
				delim_encontrado = true;
		}
	}
	return leidos;
}

void SocketComunicador::cerrarSocket() {
	// Finaliza la transmision tanto para lectura como para escritura
	shutdown(this->socket_fd, SHUT_RDWR);
	close(this->socket_fd);
	this->socket_fd = SOCKET_FD_INVALIDO;
	this->conexion_valida = false;
}

SocketComunicador::SocketComunicador(SocketComunicador && otro) :
		puerto(otro.puerto), ip(otro.ip), socket_fd(otro.socket_fd), encabezado(
				otro.encabezado), lista_direcciones(otro.lista_direcciones), conexion_valida(
				otro.conexion_valida) {
	otro.socket_fd = SOCKET_FD_INVALIDO;
	otro.conexion_valida = false;
}

SocketComunicador::~SocketComunicador() {
}

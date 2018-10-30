/*
 * SocketAceptador.h
 */

#ifndef COMUN_SOCKETS_SOCKETACEPTADOR_H_
#define COMUN_SOCKETS_SOCKETACEPTADOR_H_

#include <string>
#include <netdb.h>

#include "SocketComunicador.h"
#include "../Utiles/Excepcion.h"

#define SOCKET_FD_INVALIDO -1
#define SOCKET_VALIDO 0
#define SOCKET_INVALIDO 1

#define OPERACION_SOCKET_OK 0
#define ERROR_EN_SOCKET 1

class SocketComunicador;

/**
 * Socket TCP/IP para aceptar conexiones
 */
class SocketAceptador {
private:
	std::string puerto;
	int socket_fd;

	struct addrinfo encabezado; // suelen llamarlo hints
	struct addrinfo * res;
	bool conexion_valida;

	/**
	 * Muestra por salida estándar de error una descripción del número de
	 * error errno pasado como argumento
	 */
	void reportarError(const std::string & mensaje, int error_number);

	/**
	 * Hace el getaddrinfo y luego crea un socket TCP/IP v4.
	 * Retorna OPERACION_SOCKET_OK en caso de éxito y ERROR_EN_SOCKET
	 * en otro caso.
	 */
	int crearSocket();

	/**
	 * Hace el bind. Retorna OPERACION_SOCKET_OK en caso de éxito y
	 * ERROR_EN_SOCKET en otro caso.
	 */
	int enlazarSocket();

	/**
	 * Hace el listen(). Retorna OPERACION_SOCKET_OK en caso de éxito y
	 * ERROR_EN_SOCKET en otro caso.
	 */
	int escuchar(int cant_clientes_en_cola);

	/**
	 *
	 */
	int reusarPuerto();

public:
	/**
	 * Cuando un nuevo cliente se conecta, retona un Socket de Comunicación
	 * conectado con el cliente. En caso de error o que se haya cerrado el
	 * socket, retorna NULL
	 */
	SocketComunicador aceptarConexion() throw (std::exception);

	/**
	 * Retorna true en caso de que se haya podido crear el socket y establecer
	 * la conexion, y false si hubo algun error o si cerraron la conexión.
	 */
	bool conexionValida();

	/**
	 * Crea un socket de tipo TCP/IP v4 preparado para aceptar conexiones
	 * entrantes desde los cliente.
	 * Debe consultarse si esValido después de esta operacion
	 */
	explicit SocketAceptador(const std::string & puerto,
			int cant_clientes_en_cola) throw (std::exception);

	/**
	 * Finaliza la transmision y cierra el socket
	 */
	void cerrarSocket();

	// COPIAR SocketAceptador
	SocketAceptador(const SocketAceptador& otro) = delete;
	SocketAceptador& operator=(const SocketAceptador& otro) = delete;

	// MOVER SocketAceptador
	SocketAceptador(SocketAceptador&& otro) = delete;
	SocketAceptador& operator=(SocketAceptador&& otro) = delete;
};

#endif /* COMUN_SOCKETS_SOCKETACEPTADOR_H_ */

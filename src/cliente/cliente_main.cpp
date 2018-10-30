/*
 * cliente_main.cpp
 */

#include <exception>
#include <iostream>

#include "../comun/DefinicionesDePrueba.h"
#include "Cliente.h"

int main(int argc, char ** argv) {

	if (argc != 3) {
		std::cerr
				<< "Debe ingresar la IP del servidor y el puerto por línea de comandos"
				<< std::endl;
		return 1;
	}
	std::string ip_servidor(argv[1]);
	std::string puerto_del_servidor(argv[2]);

	try {
		Cliente cliente;
		if (!cliente.conectarseAlServer(ip_servidor, puerto_del_servidor)) {
			std::cerr << "No se pudo establecer la conexión con el servidor"
					<< std::endl;
			return 1;
		}
		cliente.iniciar();
		return 0;
	} catch (const std::exception & e) {
		std::cerr << e.what() << std::endl;
		return 1;
	} catch (...) {
		std::cerr << "Error Desconocido." << std::endl;
		return 1;
	}
}

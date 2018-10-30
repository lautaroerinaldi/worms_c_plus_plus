/*
 * servidor_main.cpp
 */

#include <exception>
#include <iostream>

#include "../comun/Protocolo/Protocolo.h"
#include "Servidor.h"

int main(int argc, char ** argv) {
	if (argc != 2){
		std::cerr << "Debe ingresar el puerto por línea de comandos" << std::endl;
		return 1;
	}
	std::string puerto(argv[1]);
	try {
		Servidor server(puerto);
		char caracter = 0;
		do {
			caracter = std::cin.get();
		} while (caracter != SALIR_MAIN);
		server.apagar();
		server.join();
		return 0;
	} catch (const std::exception & e) {
		std::cerr << e.what() << std::endl;
		return 1;
	} catch (...) {
		std::cerr << "Error Desconocido," << std::endl;
		return 1;
	}
}

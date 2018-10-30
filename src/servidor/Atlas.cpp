/*
 * Atlas.cpp
 */

#include "Atlas.h"
#include "../comun/Threads/Lock.h"

#include "../comun/DefinicionesPrivadas.h"
#include "../comun/Protocolo/Protocolo.h"

#include <queue>
#include <iostream>
#include <sstream>

#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

void Atlas::copiarColaEnVector(
		std::priority_queue<std::string, std::vector<std::string>,
				std::greater<std::string> > & cola,
		std::vector<std::string> & vector) {
	while (!cola.empty()) {
		vector.push_back(cola.top());
		cola.pop();
	}
}

std::string Atlas::getNombreEscenario(int id_escenario) {
	return archivos[id_escenario - ID_ESCENARIO_MINIMO];
}

void Atlas::filtarPorExtension(std::vector<std::string> & lista_archivos,
		const std::string & extension) {
	std::priority_queue<std::string, std::vector<std::string>,
			std::greater<std::string> > archivos_ordenados;
	for (unsigned int i = 0; i < lista_archivos.size(); ++i) {
		if (lista_archivos[i].find(extension)
				== lista_archivos[i].length() - extension.length())
			archivos_ordenados.push(lista_archivos[i]);
	}
	std::vector<std::string> archivos_filtrados_y_ordenados;
	this->copiarColaEnVector(archivos_ordenados,
			archivos_filtrados_y_ordenados);
	lista_archivos.swap(archivos_filtrados_y_ordenados);
}

bool Atlas::listarArchivos(const std::string & ruta_carpeta,
		std::vector<std::string> & lista_archivos) {
	DIR * directorio = opendir(ruta_carpeta.c_str());
	struct dirent * elemento;

	if (directorio) {
		elemento = readdir(directorio);
		while (elemento) {
			std::string nombre_completo = ruta_carpeta + '/' + elemento->d_name;
			struct stat structura;
			if (stat(nombre_completo.c_str(), &structura)
					>= 0&& S_ISREG(structura.st_mode)) {
				lista_archivos.push_back(nombre_completo);
			}
			elemento = readdir(directorio);
		}
		closedir(directorio);
	}
	if (lista_archivos.size() != 0) {
		return true;
	} else {
		std::cerr << "No hay archivos." << std::endl;
		std::flush(std::cerr);
		return false;
	}
}

Atlas::Atlas() {
	this->generarEscenarios();
}

Atlas & Atlas::getInstancia() {
	static Atlas atlas;
	return atlas;
}

void Atlas::generarEscenarios() {
	Lock lock(this->mutex);
	this->listarArchivos(RUTA_DIRECTORIO_ESCENARIOS, this->archivos);
	this->filtarPorExtension(this->archivos, EXTENSION_ESCENARIOS);
}

std::string Atlas::listarEscenarios() {
	std::ostringstream oss("");
	for (unsigned int i = 0; i < this->archivos.size(); ++i) {
		oss << DELIMITADOR_CAMPOS << (i + ID_ESCENARIO_MINIMO)
				<< DELIMITADOR_CAMPOS << archivos[i];
	}
	return oss.str();
}

unsigned int Atlas::getCantidadEscenarios() {
	return archivos.size();
}

Atlas::~Atlas() {
}

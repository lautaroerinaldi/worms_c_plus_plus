/*
 * Atlas.h
 */

#ifndef SRC_SERVIDOR_ATLAS_H_
#define SRC_SERVIDOR_ATLAS_H_

#include <string>
#include <vector>
#include <queue>
#include "../comun/Threads/Mutex.h"

class Atlas {
	Mutex mutex;
	std::vector<std::string> archivos;

	void copiarColaEnVector(
			std::priority_queue<std::string, std::vector<std::string>,
					std::greater<std::string> > & cola,
			std::vector<std::string> & vector);

	/**
	 * Dado un vector con nombres de archivos, elimina de él todos aquellos
	 * que no terminan en la extensión indicada.
	 * Luego, ordena alfabéticamente los resultados.
	 *
	 */
	void filtarPorExtension(std::vector<std::string> & lista_archivos,
			const std::string & extension);

	/**
	 * Dada la ruta de una carpeta (directorio del sistema), agrega en el
	 * vector pasado por parámetro los nombres de todos los archivos que se
	 * encuentren en la misma.
	 * Obs: No se agregan a la lista los nombres de otros directorios que se
	 * encuentren dentro del directorio original ni tampoco los nombres de los
	 * archivos que se encuentren dentro de estos subdirectorios.
	 */
	bool listarArchivos(const std::string & ruta_carpeta,
			std::vector<std::string> & lista_archivos);

	/**
	 * Recorre la lista de archivos con las extensiones filtradas, y por cada
	 * uno genera un nuevo escenario.
	 */
	void generarEscenarios();

	/**
	 * Invoca a generar escenarios.
	 */
	Atlas();

public:

	std::string getNombreEscenario(int id_escenario);

	/**
	 * Devuelve la única instancia que existe del Atlas (es Singleton)
	 */
	static Atlas & getInstancia();

	/**
	 * Retorna la cantidad de escenarios que se pudo generar (es uno por cada
	 * archivo leído de la carpeta de escenarios)
	 */
	unsigned int getCantidadEscenarios();

	/**
	 * Retorna una lista de los escenarios concatenadas en un string con la forma
	 * 	<ID_ESCENARIO> <NOMBRE_ARCHIVO>
	 */
	std::string listarEscenarios();

	~Atlas();
};

#endif /* SRC_SERVIDOR_ATLAS_H_ */

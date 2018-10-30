/*
 * Tiempo.h
 */

#ifndef COMUN_UTILES_TIEMPO_H_
#define COMUN_UTILES_TIEMPO_H_

#include <ctime>
#include <ratio>
#include <chrono>

class Tiempo {
	long int delay_en_microsegundos;
	std::chrono::high_resolution_clock::time_point t1;
	std::chrono::high_resolution_clock::time_point t2;
	long int obtenerDiferenciaEnMicrosegundos();
public:
	Tiempo(long int delay_en_microsegundos);
	~Tiempo();
};

#endif /* COMUN_UTILES_TIEMPO_H_ */

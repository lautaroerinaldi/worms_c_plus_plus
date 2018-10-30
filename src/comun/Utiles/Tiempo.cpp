/*
 * Tiempo.cpp
 */

#include "Tiempo.h"

#include <cmath>
#include <unistd.h>

Tiempo::Tiempo(long int delay_en_microsegundos) :
		delay_en_microsegundos(delay_en_microsegundos) {
	t1 = std::chrono::high_resolution_clock::now();
}

Tiempo::~Tiempo() {
	t2 = std::chrono::high_resolution_clock::now();
	long int tiempo_a_esperar = delay_en_microsegundos
			- obtenerDiferenciaEnMicrosegundos();
	if (tiempo_a_esperar > 0)
		usleep(tiempo_a_esperar);
}

long int Tiempo::obtenerDiferenciaEnMicrosegundos() {
	std::chrono::duration<double> tiempo_en_segundos =
			std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

	return lround(tiempo_en_segundos.count() * 1000000);
}

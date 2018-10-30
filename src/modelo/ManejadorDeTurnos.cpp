#include "ManejadorDeTurnos.h"
#include "../comun/Codigos.h"

#include <map>
#include <math.h>

ManejadorDeTurnos::ManejadorDeTurnos() {
	this->cantidad_gusanos = 0;
	this->estado = SIN_TURNO;
	this->id_gusano = 0;
	this->id_jugador = 0;
}

ManejadorDeTurnos::~ManejadorDeTurnos() {
}

void ManejadorDeTurnos::configurarRonda(const int cant_gusanos,
		const int cant_jugadores) {
	this->cantidad_gusanos = cant_gusanos;
	int j = 1;
	for (int i = 1; i <= cant_gusanos; i++) {
		this->gusanos.insert( { i, j });
		if ((j == cant_jugadores)) {
			j = 1;
		} else {
			j++;
		}
	}
}

int ManejadorDeTurnos::obtenerEstado() {
	return this->estado;
}

int ManejadorDeTurnos::obtenerIDGusano() {
	return this->id_gusano;
}

int ManejadorDeTurnos::obtenerIDJugador() {
	return this->id_jugador;
}

void ManejadorDeTurnos::iniciarPrimerTurno() {
	reiniciarTiempoDeInicio();
	this->estado = EN_TURNO;
	this->id_gusano = 1;
	this->id_jugador = 1;
}

bool ManejadorDeTurnos::iniciarSiguiente() {
	reiniciarTiempoDeInicio();
	if (!this->gusanos.empty()) {
		if (this->id_gusano == this->cantidad_gusanos) {
			this->id_gusano = this->gusanos.begin()->first;
			this->id_jugador = this->gusanos.begin()->second;
		} else {
			this->id_gusano++;
		}
		while (this->gusanos.find(this->id_gusano) == this->gusanos.end()) {
			if (this->id_gusano == this->cantidad_gusanos) {
				this->id_gusano = this->gusanos.begin()->first;
				this->id_jugador = this->gusanos.begin()->second;
			} else {
				this->id_gusano++;
			}
		}
		this->id_jugador = this->gusanos.at(this->id_gusano);
		this->estado = EN_TURNO;
		return true;
	}
	this->estado = SIN_TURNO;
	this->id_gusano = 0;
	this->id_jugador = 0;
	return false;
}

void ManejadorDeTurnos::removerGusano(const int id_gusano) {
	this->gusanos.erase(id_gusano);
}

void ManejadorDeTurnos::prepararFin() {
	this->estado = TERMINANDO;
}

void ManejadorDeTurnos::finalizar() {
	this->estado = TERMINADO;
}

void ManejadorDeTurnos::reiniciarTiempoDeInicio() {
	this->tiempo_de_inicio = std::chrono::high_resolution_clock::now();
}

int ManejadorDeTurnos::controlFinTurnoPorTiempo() {
	std::chrono::high_resolution_clock::time_point tiempo_actual =
			std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> tiempo_transcurrido_en_segundos =
			std::chrono::duration_cast<std::chrono::duration<double>>(
					tiempo_actual - this->tiempo_de_inicio);

	if ((tiempo_transcurrido_en_segundos.count()
			>= DURACION_DE_UN_TURNO_EN_SEGUNDOS) && (this->estado == EN_TURNO))
		this->estado = TERMINADO;

	return (round(
			DURACION_DE_UN_TURNO_EN_SEGUNDOS
					- tiempo_transcurrido_en_segundos.count()));
}

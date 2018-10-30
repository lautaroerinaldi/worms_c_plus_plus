#include "modelo/Viga.h"

#include "CodigosModelo.h"

Viga::Viga(const float lon, const float angulo, const float x,
		const float y): CuerpoMundo(VIGA), posicion_inicial(x,y) {
    this->longitud = lon;
    this->angulo = angulo;
}

Viga::~Viga() {
}

float Viga::obtenerLongitud() {
    return this->longitud;
}

float Viga::obtenerAngulo() {
    return this->angulo;
}

b2Vec2 Viga::obtenerPosicionInicial() {
    return this->posicion_inicial;
}

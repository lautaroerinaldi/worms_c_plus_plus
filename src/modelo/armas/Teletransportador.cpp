#include "Teletransportador.h"

Teletransportador::Teletransportador() {
	this->municiones_infinitas = true;
	this->municiones = 0;
	this->danio = 0;
}

Teletransportador::~Teletransportador() {
}

bool Teletransportador::disparar(Escenario& escenario, Gusano& gusano,
		b2Vec2 posicion) {
	//Solo se mueve si la posicion esta libre
	if (escenario.posicionLibre(posicion)){            
		gusano.teletransportar(posicion);
		gusano.obtenerCuerpo()->SetAwake(true);
		escenario.simularMundo();
		return true;
	}
	return false;
}

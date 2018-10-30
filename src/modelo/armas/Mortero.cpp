#include "Mortero.h"

Mortero::Mortero() {
	this->municiones_infinitas = false;
	this->municiones = 10;
	this->danio = 10;
	this->radio = 2;
}

Mortero::~Mortero() {
}

void Mortero::disparar(Bala& bala, Escenario& escenario, const int potencia) {
	if (this->municiones > 0){
		bala.configurarDanio(this->danio,this->radio);
		escenario.agregarBala(bala,true,false);
		bala.impulsar(potencia);
		this->municiones--;
	}
}

#include "Dinamita.h"

Dinamita::Dinamita() {
	this->municiones_infinitas = false;
	this->municiones = 5;
	this->danio = 50;
	this->radio = 4;
}

Dinamita::~Dinamita() {
}

void Dinamita::disparar(Bala& bala, Escenario& escenario) {
	if (this->municiones > 0){
		bala.configurarDanio(this->danio,this->radio);
		escenario.agregarBala(bala,false,false);
		bala.iniciaCronometro();
		this->municiones--;
	}
}

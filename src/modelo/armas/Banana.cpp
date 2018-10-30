#include "Banana.h"

Banana::Banana() {
	this->municiones_infinitas = false;
	this->municiones = 5;
	this->danio = 70;
	this->radio = 4;
}

Banana::~Banana() {
}

void Banana::disparar(Bala& bala, Escenario& escenario,
		const int potencia) {
	if (this->municiones > 0){
		bala.configurarDanio(this->danio,this->radio);
		escenario.agregarBala(bala,false,true);
		bala.impulsar(potencia);
		this->municiones--;
	}
}

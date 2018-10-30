#include "Bazooka.h"

Bazooka::Bazooka() {
	this->municiones_infinitas = true;
	this->danio = 50;
	this->radio = 2;
}

Bazooka::~Bazooka() {
}

void Bazooka::disparar(Bala& bala, Escenario& escenario, const int potencia) {
	bala.configurarDanio(this->danio,this->radio);
	escenario.agregarBala(bala,true,false);
	bala.impulsar(potencia);
}

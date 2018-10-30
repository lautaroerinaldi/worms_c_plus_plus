#include "GranadaSanta.h"

GranadaSanta::GranadaSanta() {
	this->municiones_infinitas = false;
	this->municiones = 2;
	this->danio = 110;
	this->radio = 8;
}

GranadaSanta::~GranadaSanta() {
}

void GranadaSanta::disparar(Bala& bala, Escenario& escenario,
		const int potencia) {
	if (this->municiones > 0){
		bala.configurarDanio(this->danio,this->radio);
		escenario.agregarBala(bala,false,false);
		bala.impulsar(potencia);
		this->municiones--;
	}
}

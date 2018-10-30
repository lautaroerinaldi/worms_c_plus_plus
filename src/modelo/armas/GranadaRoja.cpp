#include "GranadaRoja.h"

GranadaRoja::GranadaRoja() {
	this->municiones_infinitas = false;
	this->municiones = 10;
	this->danio = 30;
	this->radio = 2;
}

GranadaRoja::~GranadaRoja() {
}

void GranadaRoja::disparar(Bala& bala, Escenario& escenario,
		const int potencia) {
	if (this->municiones > 0){
		bala.configurarDanio(this->danio,this->radio);
		escenario.agregarBala(bala,false,false);
		bala.impulsar(potencia);
		this->municiones--;
	}
}

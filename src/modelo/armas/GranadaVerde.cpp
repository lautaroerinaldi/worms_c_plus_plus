#include "GranadaVerde.h"

GranadaVerde::GranadaVerde() {
	this->municiones_infinitas = true;
	this->danio = 30;
	this->radio = 2;
}

GranadaVerde::~GranadaVerde() {
}

void GranadaVerde::disparar(Bala& bala, Escenario& escenario,
		const int potencia) {
	bala.configurarDanio(this->danio,this->radio);
	escenario.agregarBala(bala,false,false);
	bala.impulsar(potencia);
}

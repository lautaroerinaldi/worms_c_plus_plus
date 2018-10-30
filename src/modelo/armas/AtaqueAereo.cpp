#include "AtaqueAereo.h"

AtaqueAereo::AtaqueAereo() {
	this->municiones_infinitas = false;
	this->municiones = 2;
	this->danio = 40;
	this->radio = 2;
}

AtaqueAereo::~AtaqueAereo() {
}

void AtaqueAereo::disparar(Escenario& escenario, std::vector<Bala*> misiles) {
	if (this->municiones > 0){
		for (int i = 0; i < 6; i++){
			Bala* bala = misiles.at(i);
			bala->configurarDanio(this->danio,this->radio);
			escenario.agregarBala(*bala, true, false);
		}
		this->municiones--;
	}
}

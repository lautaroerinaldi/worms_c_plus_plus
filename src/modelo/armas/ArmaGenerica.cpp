#include "modelo/armas/ArmaGenerica.h"

ArmaGenerica::ArmaGenerica() {
	this->municiones_infinitas = true;
	this->municiones = 0;
	this->danio = 100;
	this->radio = 0;
}

ArmaGenerica::~ArmaGenerica() {
}

bool ArmaGenerica::tieneMuniciones() {
	if (municiones_infinitas){
		return true;
	}
	return (municiones > 0);
}

void ArmaGenerica::cambiarMuniciones(const int municiones) {
	if (municiones == 9999){
		this->municiones_infinitas = true;
	} else {
		this->municiones_infinitas = false;
		this->municiones = municiones;
	}
}

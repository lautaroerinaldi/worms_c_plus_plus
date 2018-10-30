#include "modelo/Jugador.h"
#include "modelo/Gusano.h"
#include "modelo/armas/Armas.h"

#include <map>

Jugador::Jugador(const int id_jugador) {
	this->id = id_jugador;
	//Construccion del inventario
	/*0*/this->inventario.insert({BAZOOKA,Bazooka()});
	/*1*/this->inventario.insert({BANANA,Banana()});
	/*2*/this->inventario.insert({MORTERO,Mortero()});
	/*3*/this->inventario.insert({GRANADA_ROJA,GranadaRoja()});
	/*4*/this->inventario.insert({GRANADA_VERDE,GranadaVerde()});
	/*5*/this->inventario.insert({GRANADA_SANTA,GranadaSanta()});
	/*6*/this->inventario.insert({DINAMITA,Dinamita()});
	/*7*/this->inventario.insert({ATAQUE_AEREO,AtaqueAereo()});
	/*8*/this->inventario.insert({BATE_DE_BASEBALL,BateDeBaseball()});
	/*9*/this->inventario.insert({TELETRANSPORTACION,Teletransportador()});
	this->tipo_arma_activa = SIN_ARMA;
}

Jugador::~Jugador() {
}

void Jugador::asignarGusano(Gusano& gusano) {
	this->gusanos.insert({gusano.obtenerID(),gusano});
}

int Jugador::obtenerID() {
	return this->id;
}

int Jugador::cantidadGusanos() {
	return this->gusanos.size();
}

void Jugador::sumarVidasAGusanos() {
	std::map<int,Gusano&>::iterator it = this->gusanos.begin();
	for (; it != this->gusanos.end(); it++){
		it->second.sumarVida(VIDA_EXTRA);
	}
}

int Jugador::obtenerVida() {
	int vidas = 0;
	std::map<int,Gusano&>::iterator it = this->gusanos.begin();
	for (; it != this->gusanos.end(); it++){
		vidas += it->second.obtenerVida();
	}
	return vidas;
}

void Jugador::configurarInventario(std::map<int,int>& nuevas_municiones) {
	std::map<int,int>::iterator it = nuevas_municiones.begin();
	for (; it != nuevas_municiones.end(); it++){
		this->inventario.at(it->first).cambiarMuniciones(it->second);
	}
}

bool Jugador::puedeCargarArma(const int tipo_arma) {
	if (this->inventario.find(tipo_arma) != this->inventario.end()){
		this->tipo_arma_activa = tipo_arma;
		return this->inventario.at(tipo_arma).tieneMuniciones();
	}
	this->tipo_arma_activa = SIN_ARMA;
	return false;
}

ArmaGenerica* Jugador::obtenerArma() {
	return &this->inventario.at(this->tipo_arma_activa);
}

void Jugador::eliminar() {
	std::map<int,Gusano&>::iterator it = this->gusanos.begin();
	for (; it != gusanos.end(); it++){
		it->second.morir();
	}
}

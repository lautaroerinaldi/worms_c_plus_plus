#include <iostream>

#include "SdlArma.h"
#include "../../comun/Codigos.h"

SdlArma::SdlArma(): tipo(-1),conteo(5),potencia(0) {
}

int SdlArma::getConteo(){
    return this->conteo;
}

void SdlArma::setConteo(int conteo){
    this->conteo = conteo;
}

int SdlArma::getPotencia(){
    return this->potencia;
}

void SdlArma::setPotencia(int potencia){
    this->potencia = potencia;
}

int SdlArma::getTipo(){
    return this->tipo;
}

void SdlArma::setTipo(int tipo){
    this->tipo = tipo;
    this->potencia = 0;
    this->conteo = 5;
}

void SdlArma::acumularPotencia(){    
    if(this->potencia < 5){
        this->potencia++;
    }            
}

int SdlArma::tieneTiempo(){
    switch (tipo){
        case GRANADA_VERDE:
        case GRANADA_ROJA:
        case BANANA:
        case GRANADA_SANTA:
        case DINAMITA:
            return 1;                                 
        default :
            return 0;
    }
}

int SdlArma::tienePotencia(){
    switch (tipo){
        case BAZOOKA:
        case MORTERO:
        case GRANADA_VERDE:
        case GRANADA_ROJA:
        case GRANADA_SANTA:
        case BANANA:
            return 1;
        default:
            return 0;        
    }
}

SdlArma::~SdlArma() {
}


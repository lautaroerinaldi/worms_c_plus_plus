#include "SdlCamara.h"

#include "../CodigosVista.h"
#include <iostream>

SdlCamara::SdlCamara(): x(0), y(0), siguiendoBala(false) {
}

void SdlCamara::moverAbajo(){
    if(this->y < ALTO_MAPA - ALTO_PANTALLA + RANGO_MOV_CAMARA){
        this->y = this->y + RANGO_MOV_CAMARA;
        this->verificarValores();
    }        
}

void SdlCamara::moverArriba(){
    if(this->y >= RANGO_MOV_CAMARA){
        this->y = this->y - RANGO_MOV_CAMARA;
        this->verificarValores();
    }    
}

void SdlCamara::moverDerecha(){
    if(this->x < ANCHO_MAPA - ANCHO_PANTALLA){
        this->x = this->x + RANGO_MOV_CAMARA;   
        this->verificarValores();
    }    
}

void SdlCamara::moverIzquierda(){  
    if(this->x >= RANGO_MOV_CAMARA){
        this->x = this->x - RANGO_MOV_CAMARA;
        this->verificarValores();
    }    
}

int SdlCamara::convertirX(int x){
    int res = x - this->x;
    return res;
}

int SdlCamara::convertirY(int y){
    int res = y - this->y;    
    return res;
}

int SdlCamara::ajustarX(int x){
    return this->x + x;
}

int SdlCamara::ajustarY(int y){
    return this->y + y;
}

void SdlCamara::seguirGusano(int x, int y){    
    if(!this->siguiendoBala){  
        this->x = x - (ANCHO_PANTALLA / 2);
        this->y = y - (ALTO_PANTALLA / 2);    
    }
    this->verificarValores();
}

void SdlCamara::seguirBala(int x, int y){
    this->x = x - (ANCHO_PANTALLA / 2);
    this->y = y - (ALTO_PANTALLA / 2);    
    this->verificarValores();
}

void SdlCamara::verificarValores(){
    if(this->x < RANGO_MOV_CAMARA){
        this->x = 0;
    }
    if(this->y < RANGO_MOV_CAMARA){
        this->y = 0;
    }
    if(this->y > ALTO_MAPA - ALTO_PANTALLA + RANGO_MOV_CAMARA){
        this->y = ALTO_MAPA - ALTO_PANTALLA;
    }
}

void SdlCamara::activarSeguirBala() {    
    this->siguiendoBala = true;
}   

void SdlCamara::desactivarSeguirBala() {    
    this->siguiendoBala = false;
}   



SdlCamara::~SdlCamara() {
}


#include <iostream>

#include "SdlEventoMouseMovimiento.h"

#include "../elementos/SdlCamara.h"

SdlEventoMouseMovimiento::SdlEventoMouseMovimiento() {
}

int SdlEventoMouseMovimiento::procesarEvento(SDL_MouseMotionEvent &keyEvent,
                                                 SdlCamara &camara){
    if(keyEvent.x < 20){
        camara.moverIzquierda();
    }
    if(keyEvent.x > 980){
        camara.moverDerecha();
    }
    if(keyEvent.y < 20){
        camara.moverArriba();
    }
    if(keyEvent.y > 680){
        camara.moverAbajo();
    }
    return 1;
}

SdlEventoMouseMovimiento::~SdlEventoMouseMovimiento() {
}


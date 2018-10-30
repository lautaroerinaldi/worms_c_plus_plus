#include <iostream>

#include "SdlEventoMouseTeclas.h"
#include "../../comun/Codigos.h"
#include "../../comun/Destinatario.h"
#include "../../comun/Protocolo/Solicitudes/SolicitarAtacar.h"

#define ANGULO 0
#define DIRECCION 0
#define CONTEO 0

SdlEventoMouseTeclas::SdlEventoMouseTeclas(Destinatario *cliente) :
cliente(cliente) {
}

void SdlEventoMouseTeclas::procesarEvento(SDL_MouseButtonEvent& keyEvent,
        SdlGusano *jugador, SdlPartida *partida, SdlCamara &camara) {
    switch (keyEvent.type) {
        case SDL_MOUSEBUTTONDOWN:
            break;
        case SDL_MOUSEBUTTONUP:
            this->procesarAtaque(jugador, keyEvent.x, keyEvent.y,
                                                               partida, camara);
            break;
    }
}

void SdlEventoMouseTeclas::procesarAtaque(SdlGusano* jugador, int x, int y, 
                                       SdlPartida *partida, SdlCamara &camara) {
    int puedeAtacar = jugador->puedeAtacar();
    if (puedeAtacar) {
        if (jugador->getArma()->getTipo() != TELETRANSPORTACION && 
            jugador->getArma()->getTipo() != ATAQUE_AEREO) {
            partida->mostrarError("debe usar una teletransportacion o un ataque aereo para atacar con puntero");
        } else {           
            int xAjustada = camara.ajustarX(x);
            int yAjustada = camara.ajustarY(y);
            SolicitarAtacar soliAtacar(0, 0, 0, 0, xAjustada, yAjustada);            
            cliente->enviarMensaje(soliAtacar);            
        }
    }
}

SdlEventoMouseTeclas::~SdlEventoMouseTeclas() {
}


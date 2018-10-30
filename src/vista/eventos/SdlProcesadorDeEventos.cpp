#include <SDL2/SDL_stdinc.h>

#include "SdlProcesadorDeEventos.h"


SdlProcesadorDeEventos::SdlProcesadorDeEventos(Destinatario *cliente):
                        teclado(cliente),mouseTeclas(cliente) {
}

int SdlProcesadorDeEventos::procesarEvento(Uint32 &evento,SdlPartida *partida,
                        SdlGusano *jugador,std::map<std::string,
            std::shared_ptr<SdlSonido>> &sonidos,SdlInformacion &informacion,
            SdlCamara &camara) {
    if (evento == SDL_KEYDOWN) {
        SDL_KeyboardEvent &keyEvent = (SDL_KeyboardEvent&) evento;
        this->teclado.procesarEvento(keyEvent,jugador,sonidos,informacion);
    }
    if(evento == SDL_KEYUP){
        SDL_KeyboardEvent &keyEvent = (SDL_KeyboardEvent&) evento;
        this->teclado.procesarSoltado(keyEvent,partida,jugador,informacion);
    }
    if (evento == SDL_MOUSEBUTTONDOWN || evento == SDL_MOUSEBUTTONUP) {
        SDL_MouseButtonEvent &keyEvent = (SDL_MouseButtonEvent&) evento;
        this->mouseTeclas.procesarEvento(keyEvent,jugador,partida,camara);
    }
    if (evento == SDL_MOUSEMOTION) {
        SDL_MouseMotionEvent &keyEvent = (SDL_MouseMotionEvent&) evento;
        this->mouseMovimiento.procesarEvento(keyEvent,camara);
    }
    if (evento == SDL_QUIT) {
        return 0;
    }
    return 1;
}

SdlProcesadorDeEventos::~SdlProcesadorDeEventos() {
}


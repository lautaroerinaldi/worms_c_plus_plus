#ifndef SDLEVENTOMOUSETECLAS_H
#define SDLEVENTOMOUSETECLAS_H

#include <SDL2/SDL_events.h>

#include "../elementos/SdlGusano.h"
#include "../elementos/SdlPartida.h"
#include "../elementos/SdlCamara.h"

class SdlEventoMouseTeclas {
private:
    Destinatario *cliente;
    
public:
    //constructor del evento mouse por teclas
    SdlEventoMouseTeclas(Destinatario *cliente);  
    
    //procesa el evento pasado por parametro       
    void procesarEvento(SDL_MouseButtonEvent &keyEvent,SdlGusano *jugador,
                                        SdlPartida *partida, SdlCamara &camara);
    
    //procesar ataque
    void procesarAtaque(SdlGusano *jugador,int x, int y,SdlPartida *partida,
                                                             SdlCamara &camara);
    
    //destructor del evento mouse Teclas
    virtual ~SdlEventoMouseTeclas();
};

#endif /* SDLEVENTOMOUSETECLAS_H */


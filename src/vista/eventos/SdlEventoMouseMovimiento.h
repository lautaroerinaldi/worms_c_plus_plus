#ifndef SDLEVENTOMOUSEMOVIMIENTO_H
#define SDLEVENTOMOUSEMOVIMIENTO_H

#include <SDL2/SDL_events.h>
#include "../elementos/SdlCamara.h"

class SdlEventoMouseMovimiento {
private:
    SdlCamara camara;
    
public:
    //constructor del evento mouse por movimiento
    SdlEventoMouseMovimiento();   
    
    //procesa el evento pasado por parametro       
    int procesarEvento(SDL_MouseMotionEvent &keyEvent,SdlCamara &camara);    
    
    //destructor del evento mouse por movimiento
    virtual ~SdlEventoMouseMovimiento();

};

#endif /* SDLEVENTOMOUSEMOVIMIENTO_H */


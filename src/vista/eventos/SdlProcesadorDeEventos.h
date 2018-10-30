#ifndef SDLPROCESADORDEEVENTOS_H
#define SDLPROCESADORDEEVENTOS_H

#include <SDL2/SDL_stdinc.h>
#include "../elementos/SdlPartida.h"
#include "../elementos/SdlGusano.h"
#include "SdlEventoTeclado.h"
#include "SdlEventoMouseMovimiento.h"
#include "SdlEventoMouseTeclas.h"
#include "../componentes/SdlSonido.h"
#include "../elementos/SdlInformacion.h"
#include "../elementos/SdlCamara.h"

class SdlProcesadorDeEventos {
private:
    SdlEventoTeclado teclado;  
    SdlEventoMouseMovimiento mouseMovimiento;
    SdlEventoMouseTeclas mouseTeclas;      
    
public:
//constructor del procesadorDeEventos    
    SdlProcesadorDeEventos(Destinatario *cliente);
    
//procesa el evento    
    int procesarEvento(Uint32 &evento,SdlPartida *partida,SdlGusano *jugador,
                    std::map<std::string, std::shared_ptr<SdlSonido>> &sonidos,
                    SdlInformacion &informacion,SdlCamara &camara);    

//destructor del procesador de eventos    
    ~SdlProcesadorDeEventos();

};

#endif /* SDLPROCESADORDEEVENTOS_H */


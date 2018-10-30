#ifndef ESTADOLISTANDOJUGADORES_H
#define ESTADOLISTANDOJUGADORES_H

#include "EstadoJuego.h"
#include "../elementos/SdlJuego.h"

class EstadoListandoJugadores : public EstadoJuego {
private:
    SdlJuego *juego;   
    Area areaPuntero;

public:
    //constructor del estado pantalla principal
    EstadoListandoJugadores(SdlJuego *juego);

    //handlea los eventos que ocurren en la pantalla principal
    //los cuales son abajo y arriba para seleccionar y enter
    // para ingresar
    int Handle(Uint32 &evento);

    //dibuja la textura del estado
    void render(std::map<std::string, std::shared_ptr<SdlTexture>> &texturas,
            std::map<std::string, std::shared_ptr<SdlTexto>> &textos);
    
    //destructor del listando jugadores
    virtual ~EstadoListandoJugadores();
    
    //procesa la accion segun la seleccion que realizo con el puntero
    void realizoSeleccion();
};

#endif /* ESTADOLISTANDOJUGADORES_H */


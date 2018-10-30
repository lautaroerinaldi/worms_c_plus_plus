#ifndef ESTADOLISTANDOESCENARIOS_H
#define ESTADOLISTANDOESCENARIOS_H

#include <map>
#include <memory>
#include <string>

#include "EstadoJuego.h"
#include "../elementos/SdlJuego.h"
#include "../componentes/SdlTexto.h"
#include "../elementos/SdlCamara.h"

class EstadoListandoEscenarios : public EstadoJuego {
private:
    SdlJuego *juego; 
    SdlCamara camara;
    Area areaPuntero;
    std::map<int,std::string> escenarios;
    std::map<std::string, std::shared_ptr<SdlTexto>> textoPartidas;
    int cantidad;
    int posPuntero;


public:
    //constructor del estado pantalla principal
    EstadoListandoEscenarios(SdlJuego *juego, SdlCamara &camara);

    //handlea los eventos que ocurren en la pantalla principal
    //los cuales son abajo y arriba para seleccionar y enter
    // para ingresar
    int Handle(Uint32 &evento);

    //dibuja la textura del estado
    void render(std::map<std::string, std::shared_ptr<SdlTexture>> &texturas,
            std::map<std::string, std::shared_ptr<SdlTexto>> &textos);
    
    //destructor del listando jugadores
    virtual ~EstadoListandoEscenarios();
    
    //carga los textos de las partidas pasadas por parametro
    void cargarTextosPartidas();
    
    //procesa la accion segun la seleccion que realizo con el puntero
    void realizoSeleccion();
};


#endif /* ESTADOLISTANDOESCENARIOS_H */


#include "EstadoPantallaFinalizada.h"

#include "../componentes/Area.h"


EstadoPantallaFinalizada::EstadoPantallaFinalizada(std::map<std::string,
                                std::shared_ptr<SdlTexture>> &texturas,
        std::map<std::string, std::shared_ptr<SdlTexto>> &textos):
                texturas(texturas),textos(textos), 
                animacionGanador(texturas.at("wwinner")),
                animacionPerdedor(texturas.at("wsurndr")){
}

void EstadoPantallaFinalizada::mostrarPantalla(bool soyGanador){
    if(soyGanador){
        this->mostrarGanador();
    }else{
        this->mostrarPerdedor();
    }    
}

void EstadoPantallaFinalizada::mostrarGanador(){
    Area areaHeader(0, 0, 1200, 200);
    Area areaGanador(200, 200, 700, 120);
    Area gusanoAnimandoGanando(400,400,150,150);
    Area sdlSrc(0, 0, 1024, 768);
    
    texturas.at("header")->renderFijo(sdlSrc,areaHeader, 0, SDL_FLIP_NONE ,0);  
    textos.at("ganador")->renderFijo(areaGanador, 2);
    animacionGanador.animarCarga(gusanoAnimandoGanando); 
}

void EstadoPantallaFinalizada::mostrarPerdedor(){
    Area areaHeader(0, 0, 1200, 200);
    Area areaPerdedor(200, 200, 700, 120);
    Area gusanoAnimandoPerdiendo(400,400,150,150);
    Area sdlSrc(0, 0, 1024, 768);
    texturas.at("header")->renderFijo(sdlSrc,areaHeader, 0, SDL_FLIP_NONE ,0);
    textos.at("perdedor")->renderFijo(areaPerdedor, 1);
    animacionPerdedor.animarCarga(gusanoAnimandoPerdiendo);
}

EstadoPantallaFinalizada::~EstadoPantallaFinalizada() {
}


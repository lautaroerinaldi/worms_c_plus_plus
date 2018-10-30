#ifndef ESTADOPANTALLAFINALIZADA_H
#define ESTADOPANTALLAFINALIZADA_H

#include <map>
#include <memory>

#include "../componentes/SdlTexture.h"
#include "../componentes/SdlTexto.h"
#include "../componentes/SdlAnimation.h"

class EstadoPantallaFinalizada {
private:
    std::map<std::string, std::shared_ptr<SdlTexture>> texturas;
    std::map<std::string, std::shared_ptr<SdlTexto>> textos;
    SdlAnimation animacionGanador;
    SdlAnimation animacionPerdedor;
    
public:
    //constructor de la pantalla finalizada    
    EstadoPantallaFinalizada(std::map<std::string, std::shared_ptr<SdlTexture>>
                                        &texturas,
            std::map<std::string, std::shared_ptr<SdlTexto>> &textos);
    
    //muestra la pantalla
    void mostrarPantalla(bool soyGanador);
    
    //mostrar pantalla ganador
    void mostrarGanador();
    
    //mostrar pantalla perdedor
    void mostrarPerdedor();
    
    //destructor de la pantalla finalizada
    virtual ~EstadoPantallaFinalizada();
};

#endif /* ESTADOPANTALLAFINALIZADA_H */


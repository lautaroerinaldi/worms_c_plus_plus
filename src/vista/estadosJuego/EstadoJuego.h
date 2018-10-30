#ifndef ESTADOJUEGO_H
#define ESTADOJUEGO_H

#include <map>
#include <memory>
#include <string>
#include "../componentes/SdlTexture.h"
#include "../componentes/Area.h"
#include "../componentes/SdlTexto.h"

class EstadoJuego {
private:
    
public:
    //constructor del estado juego
    EstadoJuego();   
    
    //deriva a las clases hijas el handle
    virtual int Handle(Uint32 &evento) = 0;
    
    //dibuja la textura del estado
    virtual void render(
            std::map<std::string,std::shared_ptr<SdlTexture>> &texturas,
                    std::map<std::string, std::shared_ptr<SdlTexto>> &textos) = 0;    
    
    //destructor del estado juego
    virtual ~EstadoJuego();

};

#endif /* ESTADOJUEGO_H */


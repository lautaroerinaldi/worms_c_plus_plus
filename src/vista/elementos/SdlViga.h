#ifndef SDLVIGA_H
#define SDLVIGA_H

#include <memory>
#include "../componentes/Area.h"
#include "../componentes/SdlTexture.h"

class SdlViga {
private:
    std::shared_ptr<SdlTexture> textura;
    Area area;    
    int grado; 
    
public:
//constructor de la viga    
    SdlViga(const Area &area,std::shared_ptr<SdlTexture> textura,int grado);

//dibuja la viga en el mapa    
    int dibujar();  
    
//llama al destructor de la viga    
    virtual ~SdlViga();
};

#endif


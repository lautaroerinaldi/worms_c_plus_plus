#include "SdlViga.h"

SdlViga::SdlViga(const Area &area,std::shared_ptr<SdlTexture> textura,int grado):
                 textura(textura),area(std::move(area)),grado(grado){
}

int SdlViga::dibujar(){    
    return textura->dibujar(area,this->grado);    
}

SdlViga::~SdlViga() {
}


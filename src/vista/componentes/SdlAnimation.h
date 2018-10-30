#ifndef SDLANIMATION_H
#define SDLANIMATION_H

#include <memory>
#include "SdlTexture.h"
#include "Area.h"

class SdlAnimation {
private:
    std::shared_ptr<SdlTexture> &texture;
    int frameAncho, frameAlto;
    int textureAncho, textureAlto;
    Area inicio;

public:
    //constructor    
    SdlAnimation(std::shared_ptr<SdlTexture> &texture);

    //carga la informacion necesaria para la animacion
    void loadAnimation();
    
    //anima el sprite
    int animar(const Area& dest,int angulo, int direccion, int color);
    
    //anima la carga del sprite
    int animarCarga(const Area& dest);
    
    //devuelve el inicio del sprite
    Area getInicio();
    
    //setea el inicio del sprite
    void setInicio(Area inicio);

    //devuelve el alto del frame
    int getFrameAlto();
    
    //devuelve el alto de la textura
    int getTextureAlto();
    
    //ubica la posicion en el sprite del medio
    void ubicarEnElMedio(int direccion);
    
    //carga el inicio del sprite en la ultima imagen
    void cargarDesdeElUltimo();
    
    //destructor    
    virtual ~SdlAnimation();

};

#endif


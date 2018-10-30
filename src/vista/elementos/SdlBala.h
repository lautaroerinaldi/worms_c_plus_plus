#ifndef SDLBALA_H
#define SDLBALA_H

#include "../componentes/SdlAnimation.h"
#include "../componentes/SdlTexture.h"
#include "../componentes/Area.h"

class SdlBala {
private:
    Area area;
    std::shared_ptr<SdlTexture> textura;
    SdlAnimation animacion;
    std::shared_ptr<SdlTexture> texturaExplosion;
    SdlAnimation animacionExplosion;    
    int grado;
    bool impacto;
    int radio;
    int tipo;
    
public:
    //constructor de la bala
    SdlBala(const Area &area,std::shared_ptr<SdlTexture> &textura,
            int grado,std::shared_ptr<SdlTexture> &texturaExplosion, int tipo);

    //dibuja la bala en el mapa    
    void dibujar();  
    
    //mueve la bala
    void mover(int x, int y, int angulo);
        
    //impacta la bala
    void impactar(int radio);
    
    //anima la bala
    void animarBala();
    
    //devuelve el tipo de la bala
    int getTipo();

    //destructor de la bala
    virtual ~SdlBala();
};

#endif /* SDLBALA_H */


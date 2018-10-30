#ifndef STATE_H
#define STATE_H

#include <string>
#include <memory>
#include "../componentes/Area.h"
#include "../componentes/SdlTexture.h"


class State {
private:
    
public:
    //constructor del estado
    State();

    //deriva a las clases hijas el handle
    virtual int Handle(const std::string &nombreSprite) = 0;

    //renderiza la animacion del estado
    virtual void render(Area &posicion,int direccion,int color) = 0;

    //realiza un movimiento del estado segun el estado en el que se encuentre
    virtual void mover(int direccion) = 0;
    
    //devuelve true si corresponde a un cambio de direccion
    //o false si corresponde a un cambio de estado
    virtual int direccionar() = 0;
    
    //devuelve si el estado puede atacar
    virtual int puedeAtacar() = 0;
    
    //devuelve el angulo en el que se encuentra el gusano
    virtual int getAngulo() = 0;
    
    //deriva alas clases hijas para que se destruyan
    virtual ~State();
};

#endif /* STATE_H */

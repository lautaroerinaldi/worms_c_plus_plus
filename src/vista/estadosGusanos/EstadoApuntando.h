#ifndef ESTADOAPUNTANDO_H
#define ESTADOAPUNTANDO_H

#include "State.h"
#include "../elementos/SdlGusano.h"
#include "../componentes/SdlAnimation.h"
#include "../componentes/SdlTexture.h"
#include "../componentes/Area.h"

#define MOVIMIENTO_ANGULO 5.625f

class EstadoApuntando : public State {
private:
    std::shared_ptr<SdlTexture> &textura;
    SdlAnimation animacion;
    float angulo;

public:
    //constructor del estado animando fijo
    EstadoApuntando(std::shared_ptr<SdlTexture> &textura,int direccion);

    //handlea el nuevo estado
    int Handle(const std::string &nombreSprite);

    //renderiza la imagen
    void render(Area &posicion,int direccion, int color);

    //actualiza el inicio del sprite segun la logica de apuntando, 
    //la cual responde al evento y mueve el sprite segun el angulo
    void actualizarInicioSprite();

    //mueve la punteria segun la direccion pasada por parametro    
    void mover(int direccion);

    //destructor del estado Lazy
    virtual ~EstadoApuntando();

    //disminuye la punteria
    void disminuirPunteria();
    
    //aumentar punteria
    void aumentarPunteria();
    
    
    //devuelve true ya que se refiere a un cambio de direccion al apuntar
    int direccionar();
    
    //setea el angulo donde esta apuntando
    void setAngulo(float angulo);
    
    //consulta si puede atacar
    int puedeAtacar();
    
    //devuelve el angulo de donde esta apuntando
    int getAngulo();
};

#endif /* ESTADOAPUNTANDO_H */


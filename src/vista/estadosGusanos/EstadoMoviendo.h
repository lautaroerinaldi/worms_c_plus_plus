#ifndef ESTADOMOVIENDO_H
#define ESTADOMOVIENDO_H

#include "State.h"
#include "../elementos/SdlGusano.h"
#include "../componentes/SdlAnimation.h"
#include "../componentes/SdlTexture.h"
#include "../componentes/Area.h"

class EstadoMoviendo : public State{
private:
    std::shared_ptr<SdlTexture> &textura;
    SdlAnimation animacion;
        
public:
    //constructor del estado Moviendo
    EstadoMoviendo(std::shared_ptr<SdlTexture> &textura);
    
    //handlea el nuevo estado
    int Handle(const std::string &nombreSprite);

    //renderiza la imagen
    void render(Area &posicion,int direccion, int color);
    
    //actualiza el inicio del sprite segun la logica caminando, la cual
    //por cada movimiento que recibe mueve la imagen
    void actualizarInicioSprite();
    
    
    //mueve el gusano animandolo
    void mover(int direccion);
           
    
    //devuelve 2 para verificar si se encontraba yendo para esa direccion
    int direccionar();
    
    //consulta si puede atacar
    int puedeAtacar();

    //devuelve el angulo del gusano
    int getAngulo();
    
    //destructor del estado Lazy
    virtual ~EstadoMoviendo();
};

#endif /* ESTADOLAZY_H */


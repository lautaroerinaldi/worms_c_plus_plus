#ifndef ESTADOMURIENDO_H
#define ESTADOMURIENDO_H


#include "State.h"
#include "../elementos/SdlGusano.h"
#include "../componentes/SdlAnimation.h"
#include "../componentes/SdlTexture.h"
#include "../componentes/Area.h"

class EstadoMuriendo : public State{
private:
    std::shared_ptr<SdlTexture> &textura;
    SdlAnimation animacion;
        
public:
    //constructor del estado cargando arma
    EstadoMuriendo(std::shared_ptr<SdlTexture> &textura);        

    //handlea el nuevo estado
    int Handle(const std::string &nombreSprite);

    //renderiza la imagen
    void render(Area &posicion,int direccion,int color);
    
    //actualiza el inicio del sprite segun la logica lazy, la cual simplemente 
    //muestra la siguiente imagen del sprite
    void actualizarInicioSprite();
    
    //no aplica al cargar arma
    void mover(int direccion);

    //devuelve true ya que se refiere a un cambio de direccion al cargar arma
    int direccionar();
        
    //consulta si puede atacar
    int puedeAtacar();
    
    //devuelve el angulo del gusano
    int getAngulo();
    
    //destructor del estado Atacando
    virtual ~EstadoMuriendo();
};


#endif /* ESTADOMURIENDO_H */


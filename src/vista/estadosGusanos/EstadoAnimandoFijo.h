#ifndef ESTADOANIMANDOFIJO_H
#define ESTADOANIMANDOFIJO_H

#include "State.h"
#include "../elementos/SdlGusano.h"
#include "../componentes/SdlAnimation.h"
#include "../componentes/SdlTexture.h"
#include "../componentes/Area.h"

class EstadoAnimandoFijo : public State{
private:
    std::shared_ptr<SdlTexture> &textura;
    SdlAnimation animacion;
        
public:
    //constructor del estado animando fijo
    EstadoAnimandoFijo(std::shared_ptr<SdlTexture> &textura);        

    //handlea el nuevo estado
    int Handle(const std::string &nombreSprite);

    //renderiza la imagen
    void render(Area &posicion,int direccion, int color);
    
    //actualiza el inicio del sprite segun la logica lazy, la cual simplemente 
    //muestra la siguiente imagen del sprite
    void actualizarInicioSprite();
    
    //no aplica al estado animando fijo    
    void mover(int direccion);

    //devuelve false ya que la animacion fija no tiene eventos asociados a la
    //direccion
    int direccionar();
    
    //consulta si puede atacar
    int puedeAtacar();
    
    //devuelve el angulo del gusano
    int getAngulo();
    
    //destructor del estado Lazy
    virtual ~EstadoAnimandoFijo();
};

#endif /* ESTADOLAZY_H */


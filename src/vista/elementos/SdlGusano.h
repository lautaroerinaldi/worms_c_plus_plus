#ifndef SDLGUSANO_H
#define SDLGUSANO_H

#include <memory>
#include "../estadosGusanos/State.h"
#include "../../comun/Codigos.h"
#include "../componentes/SdlTexto.h"
#include "SdlArma.h"

class SdlGusano {
private:
    int id;
    Area posicion;      
    int color;
    int vida;
    std::shared_ptr<State> estado;      
    
    int direccion;
    int inclinacion;
    SdlArma arma;

public:
    //constructor del gusano    
    SdlGusano(int id, Area &area, int color, int vida,
                                            std::shared_ptr<State> estado);
    
    //muestra la animacion de un gusano en el mapa
    void animar(std::map<std::string, std::shared_ptr<SdlTexto>> &textos);

    //renderiza la imagen del jugador
    void render();

    //setea el nuevo estado
    void setEstado(std::shared_ptr<State> estado);

    //handlea el nuevo estado
    int handle(const std::string &nombreSprite);

    //devuelve la posicion que se encuentra el gusano
    Area getPosicion();

    //setea la nueva posicion del gusano
    void setPosicion(Area &posicion);

    //devuelve la direccion adonde mira el gusano
    int getDireccion();
    
    //setea la direccion del gusano que puede ser izquierda o derecha
    void setDireccion(int direccion);            
    
    //devuelve la inclinacion del gusano que puede ser abajo, normal o arriba   
    int getInclinacion();
    
    //setea la inclinacion del gusano
    void setInclinacion(int inclinacion);
           
    //mueve al gusano
    void mover(int x, int y);
    
    //devuelve un puntero del arma que tiene el gusano
    SdlArma* getArma();
    
    //setea una nueva arma
    void setArma(int arma);
    
    //devuelve el id que tiene el gusano
    int getId();
    
    //actualiza la punteria
    void actualizarPunteria(int direccionDeLaPunteria);
    
    //verifica y actualiza si corresponde segun el estado.
    //si el estado corresponde modifica la direccion del gusano
    //sino devuelve un 0 si corrresponde a un cambio de estado de movimiento
    int direccionar(int direccion);

    //consulta a los estados si puede atacar
    int puedeAtacar();
    

    //devuelve el angulo de la mira
    int getAngulo();
    
    //devuelve la vida del gusano
    int getVida();
    
    //setea la vida del gusano
    void setVida(int vida);
    
    //destructor del gusano    
    virtual ~SdlGusano();
};

#endif


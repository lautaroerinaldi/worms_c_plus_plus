#ifndef SDLCAMARA_H
#define SDLCAMARA_H

class SdlCamara {
private:    
    int x;
    int y;
    bool siguiendoBala;
    
public:
    //constructor de la camara
    SdlCamara();   
    
    //mueve la camara a la izquierda
    void moverIzquierda();
    
    //mueve la camara a la derecha
    void moverDerecha();
    
    //mueve la camara para arriba
    void moverArriba();
    
    //mueve la camara para abajo
    void moverAbajo();
    
    //convertir x
    int convertirX(int x);
    
    //convertir y
    int convertirY(int y);
    
    //ajustar x
    int ajustarX(int x);
    
    //ajustar y
    int ajustarY(int y);
    
    //la camara sigue al gusano
    void seguirGusano(int x, int y);    
    
    //la camara sigue a la bala
    void seguirBala(int x, int y);
        
    //activa la camara para seguir a la bala
    void activarSeguirBala();
    
    //desactiva la camara para que deje de seguir la bala
    void desactivarSeguirBala();
    
    //verifica los valores para que no sean negativos
    void verificarValores();
    
    //destructor de la camara
    virtual ~SdlCamara();
    
};

#endif /* SDLCAMARA_H */


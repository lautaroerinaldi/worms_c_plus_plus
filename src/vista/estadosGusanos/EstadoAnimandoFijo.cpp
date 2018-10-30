#include <iostream>

#include "EstadoAnimandoFijo.h"

EstadoAnimandoFijo::EstadoAnimandoFijo(std::shared_ptr<SdlTexture> &textura):
                                        textura(textura),animacion(textura){
}

int EstadoAnimandoFijo::Handle(const std::string &nombreSprite) {
    std::string nombre = "img/"+nombreSprite+".png";
    return nombre == this->textura->getNombreTextura();
}

void EstadoAnimandoFijo::render(Area &posicion,int direccion, int color) {
    this->actualizarInicioSprite();
    int respuesta = animacion.animar(posicion, 0, direccion, color);       
    if (respuesta < 0) {
        printf("NO SE PUDO MOSTRAR EL PROYECTIL!\n");
    }
}

void EstadoAnimandoFijo::actualizarInicioSprite() {
    Area inicio = this->animacion.getInicio();
    inicio.setY(inicio.getY() + this->animacion.getFrameAlto());
    if (inicio.getY() >= this->animacion.getTextureAlto()) {                
        inicio.setY(0);        
    }
    this->animacion.setInicio(inicio);
}

void EstadoAnimandoFijo::mover(int direccion){    
}


int EstadoAnimandoFijo::direccionar(){
    return 0;
}

int EstadoAnimandoFijo::puedeAtacar(){
    return 0;
}

int EstadoAnimandoFijo::getAngulo(){
    return -1;
}

EstadoAnimandoFijo::~EstadoAnimandoFijo() {
}


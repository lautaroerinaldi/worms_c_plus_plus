#include <iostream>

#include "EstadoCargandoArma.h"

#define PUNTERIA_OK 2

EstadoCargandoArma::EstadoCargandoArma(std::shared_ptr<SdlTexture> &textura):
                            textura(textura),animacion(textura){
}

int EstadoCargandoArma::Handle(const std::string &nombreSprite) {
    if(nombreSprite == "punteria"){
        return PUNTERIA_OK;
    }
    std::string nombre = "img/"+nombreSprite+".png";
    return nombre == this->textura->getNombreTextura();            
}

void EstadoCargandoArma::render(Area &posicion,int direccion, int color) {
    this->actualizarInicioSprite();
    int respuesta = animacion.animar(posicion, 0, direccion, color);
    if (respuesta < 0) {
        printf("NO SE PUDO MOSTRAR EL PROYECTIL!\n");
    }
}

void EstadoCargandoArma::actualizarInicioSprite() {
    Area inicio = this->animacion.getInicio();
    if (inicio.getY() < (this->animacion.getTextureAlto() - this->animacion.getFrameAlto())) {
        inicio.setY(inicio.getY() + this->animacion.getFrameAlto());
    }
    this->animacion.setInicio(inicio);
}

void EstadoCargandoArma::mover(int direccion){    
}

int EstadoCargandoArma::direccionar(){
    return 1;
}

int EstadoCargandoArma::puedeAtacar(){
    return 1;
}

int EstadoCargandoArma::getAngulo(){
    return 0;
}

EstadoCargandoArma::~EstadoCargandoArma() {
}


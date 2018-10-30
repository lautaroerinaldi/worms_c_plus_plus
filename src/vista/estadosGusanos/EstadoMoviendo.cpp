#include <iostream>

#include "EstadoMoviendo.h"

EstadoMoviendo::EstadoMoviendo(std::shared_ptr<SdlTexture> &textura): 
                                        textura(textura),animacion(textura){
}


int EstadoMoviendo::Handle(const std::string &nombreSprite) {
    std::string nombre = "img/"+nombreSprite+".png";
    return nombre == this->textura->getNombreTextura();
}


void EstadoMoviendo::render(Area &posicion,int direccion, int color) {
    this->actualizarInicioSprite();
    int respuesta = animacion.animar(posicion, 0, direccion, color);
    if (respuesta < 0) {
        printf("NO SE PUDO MOSTRAR EL PROYECTIL!\n");
    }
}


void EstadoMoviendo::mover(int direccion){
    Area inicio = this->animacion.getInicio();
    inicio.setY(inicio.getY() + this->animacion.getFrameAlto());
    if (inicio.getY() >= this->animacion.getTextureAlto()) {                
        inicio.setY(0);        
    }
    this->animacion.setInicio(inicio);
}

void EstadoMoviendo::actualizarInicioSprite() {
}

int EstadoMoviendo::direccionar(){
    return 2;
}

int EstadoMoviendo::puedeAtacar(){
    return 0;
}

int EstadoMoviendo::getAngulo(){
    return -1;
}

EstadoMoviendo::~EstadoMoviendo() {
}

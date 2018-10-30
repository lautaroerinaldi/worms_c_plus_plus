#include <iostream>

#include "EstadoApuntando.h"

EstadoApuntando::EstadoApuntando(std::shared_ptr<SdlTexture> &textura,
        int direccion) : textura(textura), animacion(textura) {
    if (direccion) {
        angulo = +MOVIMIENTO_ANGULO;
    } else {
        angulo = -MOVIMIENTO_ANGULO;
    }
    this->animacion.ubicarEnElMedio(direccion);
}

int EstadoApuntando::Handle(const std::string &nombreSprite) {
    return nombreSprite == "punteria";
}

void EstadoApuntando::render(Area &posicion,int direccion, int color) {
    int respuesta = animacion.animar(posicion, 0, direccion, color);
    if (respuesta < 0) {
        printf("NO SE PUDO MOSTRAR EL PROYECTIL!\n");
    }
}

void EstadoApuntando::mover(int direccion) {
    if (direccion == 0) {
        this->disminuirPunteria();
    } else {
        this->aumentarPunteria();
    }
}

void EstadoApuntando::aumentarPunteria() {
    Area inicio = this->animacion.getInicio();
    if (inicio.getY() < this->animacion.getTextureAlto() - this->animacion.getFrameAlto()) {
        this->angulo += MOVIMIENTO_ANGULO;
        if (this->angulo) {
            inicio.setY(inicio.getY() + this->animacion.getFrameAlto());
        }
    }
    this->animacion.setInicio(inicio);
}

void EstadoApuntando::disminuirPunteria() {
    Area inicio = this->animacion.getInicio();
    if (inicio.getY() >= this->animacion.getFrameAlto()) {
        this->angulo -= MOVIMIENTO_ANGULO;
        if (this->angulo) {
            inicio.setY(inicio.getY() - this->animacion.getFrameAlto());
        }
    }
    this->animacion.setInicio(inicio);
}

void EstadoApuntando::setAngulo(float angulo) {
    this->angulo = angulo;
}


int EstadoApuntando::direccionar(){
    return 1;
}

int EstadoApuntando::puedeAtacar(){
    return 1;
}

int EstadoApuntando::getAngulo(){
    return (int)this->angulo;
}

EstadoApuntando::~EstadoApuntando() {
}

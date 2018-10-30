#include <iostream>

#include "SdlBala.h"
#include "../../comun/Codigos.h"

SdlBala::SdlBala(const Area &area, std::shared_ptr<SdlTexture> &textura,
        int grado, std::shared_ptr<SdlTexture> &texturaExplosion, int tipo) :
area(std::move(area)), textura(textura), animacion(textura),
texturaExplosion(texturaExplosion), animacionExplosion(texturaExplosion),
grado(grado), impacto(false), radio(0), tipo(tipo) {
}

void SdlBala::dibujar() {
    int respuesta;
    if (this->impacto) {
        this->area.setX(this->area.getX() - this->radio);
        this->area.setY(this->area.getY() - this->radio);
        this->area.setHeight(this->radio * 2);
        this->area.setWidth(this->radio * 2);
        respuesta = this->animacionExplosion.animar(this->area, 0, 1, 0);
    } else {
        this->animarBala();
        respuesta = this->animacion.animar(this->area, 0, 1, 0);
    }
    if (respuesta < 0) {
        printf("NO SE PUDO MOSTRAR EL PROYECTIL!\n");
    }
}

void SdlBala::mover(int x, int y, int angulo) {
    this->area.setX(x);
    this->area.setY(y);
    this->grado = angulo;
}

void SdlBala::impactar(int radio) {
    this->radio = radio;
    this->impacto = true;
}

void SdlBala::animarBala() {
    if (this->tipo != ATAQUE_AEREO) {
        Area inicio = this->animacion.getInicio();
        inicio.setY(inicio.getY() + this->animacion.getFrameAlto());
        if (inicio.getY() >= this->animacion.getTextureAlto()) {
            inicio.setY(0);
        }
        this->animacion.setInicio(inicio);
    }
}

int SdlBala::getTipo(){
    return this->tipo;
}

SdlBala::~SdlBala() {
}


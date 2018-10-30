#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <iostream>
#include "SdlAnimation.h"
#include "SdlWindow.h"
#include "SdlException.h"

#define AJUSTE 30

SdlAnimation::SdlAnimation(std::shared_ptr<SdlTexture> &textura) :
texture(textura), inicio(0, 0, 0, 0) {
    this->loadAnimation();
}

void SdlAnimation::loadAnimation() {                
    SDL_QueryTexture(this->texture->getTextura(), NULL, NULL,
            &this->textureAncho, &this->textureAlto);
    int cantidadDeImagenes = this->textureAlto / this->textureAncho;
    this->frameAncho = this->textureAncho / 1;
    this->frameAlto = this->textureAlto / cantidadDeImagenes;
    inicio.setWidth(this->frameAncho);
    inicio.setHeight(this->frameAlto);
}

int SdlAnimation::animarCarga(const Area& dest) {
    this->inicio.setY(this->inicio.getY() + this->frameAlto);    
    if (this->inicio.getY() >= textureAlto) {
        this->inicio.setY(0);
    }
    return this->texture->renderFijo(this->inicio,dest,0,SDL_FLIP_NONE, -1);
}

int SdlAnimation::animar(const Area& dest,int angulo, int direccion, int color){
    SDL_RendererFlip flip;
    if (direccion){
        flip = SDL_FLIP_HORIZONTAL;
    }else{
        flip = SDL_FLIP_NONE;
    }    
     Area destino(dest.getX() - (AJUSTE / 2),dest.getY() - (AJUSTE / 2),
                dest.getWidth() + AJUSTE, dest.getHeight() + AJUSTE);     
    return this->texture->render(this->inicio, destino, angulo, flip, color);
}

Area SdlAnimation::getInicio() {
    return this->inicio;
}

void SdlAnimation::setInicio(Area inicio) {
    this->inicio = inicio;
}

int SdlAnimation::getFrameAlto() {
    return this->frameAlto;
}

int SdlAnimation::getTextureAlto() {
    return this->textureAlto;
}

void SdlAnimation::ubicarEnElMedio(int direccion){
    int cantidadDeImagenes = this->textureAlto / this->frameAlto;
    int medio = cantidadDeImagenes/2;    
    this->inicio.setY((medio +(direccion - 1)) * this->frameAlto);    
}

void SdlAnimation::cargarDesdeElUltimo() {
    this->inicio.setY(this->textureAlto);
}


SdlAnimation::~SdlAnimation() {

}


#include "SdlTexture.h"
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>
#include "SdlException.h"
#include "../CodigosVista.h"

#define MASK 0, 0, 0


SdlTexture::SdlTexture(const std::string &filename, const SdlWindow& window,
                                                              SdlCamara &camara)
: renderer(window.getRenderer()), nombreSprite(filename), camara(camara) {
    this->texture = loadTexture(filename);
}


SdlTexture::~SdlTexture() {
    SDL_DestroyTexture(this->texture);
}

SDL_Texture* SdlTexture::loadTexture(const std::string &filename) {
    SDL_Surface *surface = IMG_Load(filename.c_str());
    if (!surface) {
        throw SdlException("Error al cargar el surface", SDL_GetError());
    }
    SDL_Surface *fondo = IMG_Load("img/fondoWorms.jpeg");
    if (!fondo) {
        throw SdlException("Error al cargar la el fondo", SDL_GetError());
    }
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(fondo->format, MASK));
    this->texture = SDL_CreateTextureFromSurface(this->renderer, surface);
    if (!texture) {
        throw SdlException("Error al cargar la textura", SDL_GetError());
    }
    SDL_FreeSurface(surface);
    SDL_FreeSurface(fondo);
    return this->texture;
}

int SdlTexture::render(const Area& src, const Area& dest,
        int angulo, SDL_RendererFlip flip, int color) {
    int x = this->camara.convertirX(dest.getX());
    int y = this->camara.convertirY(dest.getY());
    SDL_Rect sdlSrc = {
        src.getX(), src.getY(),
        src.getWidth(), src.getHeight()
    };    
    SDL_Rect sdlDest = {
        x, y,
        dest.getWidth(), dest.getHeight()
    };
    if (color > 0) {
        this->asignarColores(color);
    }
    return SDL_RenderCopyEx(this->renderer, this->texture, &sdlSrc, &sdlDest,
            angulo, NULL, flip);
}

int SdlTexture::renderFijo(const Area& src, const Area& dest,
        int angulo, SDL_RendererFlip flip, int color) {
    SDL_Rect sdlSrc = {
        src.getX(), src.getY(),
        src.getWidth(), src.getHeight()
    };    
    SDL_Rect sdlDest = {
        dest.getX(), dest.getY(),
        dest.getWidth(), dest.getHeight()
    };
    if (color > 0) {
        this->asignarColores(color);
    }
    return SDL_RenderCopyEx(this->renderer, this->texture, &sdlSrc, &sdlDest,
            angulo, NULL, flip);
}

int SdlTexture::renderMain() const {
    return SDL_RenderCopy(this->renderer, this->texture, NULL, NULL);
}

SDL_Texture * SdlTexture::getTextura() {
    return this->texture;
}

int SdlTexture::dibujar(Area & dest, int grado) {
    Area sdlSrc(0, 0, 1024, 768);
    this->render(sdlSrc, dest, grado, SDL_FLIP_NONE, 0);
    return 0;
}

void SdlTexture::asignarColores(int color) {
    switch (color) {
        case 1:
            SDL_SetTextureColorMod(this->texture, ROJO);
            break;
        case 2:
            SDL_SetTextureColorMod(this->texture, CELESTE);
            break;
        case 3:
            SDL_SetTextureColorMod(this->texture, VERDE);
            break;
        case 4:
            SDL_SetTextureColorMod(this->texture, AMARILLO);
            break;
        case 5:
            SDL_SetTextureColorMod(this->texture, AZUL);
            break;
        case 6:
            SDL_SetTextureColorMod(this->texture, FUCSIA);
            break;
    }
}

std::string SdlTexture::getNombreTextura() const {
    return this->nombreSprite;
}

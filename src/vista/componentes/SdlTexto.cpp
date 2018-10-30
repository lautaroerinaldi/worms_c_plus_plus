#include <map>
#include <iostream>

#include "SdlTexto.h"
#include "../CodigosVista.h"

SdlTexto::SdlTexto(const std::string& text, const std::string& fontPath, 
                                   int size, SdlCamara &camara):camara(camara){
    if (TTF_Init() == -1) {
        throw SdlException("Error al inicializar libreria", TTF_GetError());
    }
    SdlWindow *window = SdlWindow::instance();
    if (!SdlWindow::inicializado()) {
        throw SdlException("Error ventana", TTF_GetError());
    }
    this->renderer = window->getRenderer();
    this->textura = this->getText(text, fontPath, size);
    SDL_QueryTexture(this->textura, NULL, NULL, &this->textureAncho,
            &this->textureAlto);

}

SDL_Texture* SdlTexto::createTextTexture(TTF_Font* font, std::string text) {
    SDL_Color color;
    color = {BLANCO,0};
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(),color);
    if (!surface) {
        throw SdlException("Error al cargar la textura de texto", TTF_GetError());
    }
    SDL_Texture* tex = SDL_CreateTextureFromSurface(this->renderer, surface);
    if (!tex) {
        throw SdlException("Error al cargar la textura", TTF_GetError());
    }
    SDL_FreeSurface(surface);
    return tex;
}

TTF_Font* SdlTexto::getFont(std::string nombreFont, int size) {
    fuente = TTF_OpenFont(nombreFont.c_str(), size);
    if (fuente == NULL) {
        throw SdlException("Error al cargar la fuentte", TTF_GetError());
    }
    return fuente;
}

SDL_Texture* SdlTexto::getText(std::string text, std::string nombreArch, int size) {
    TTF_Font* font = this->getFont(nombreArch, size);

    this->textos = this->createTextTexture(font, text);

    return this->textos;
}

void SdlTexto::render(const Area& dest, int color) {
    SDL_Rect sdlSrc = {0, 0, 1024, 768};
    int x = this->camara.convertirX(dest.getX());
    int y = this->camara.convertirY(dest.getY());
    SDL_Rect sdlFin = {
        x, y,
        dest.getWidth(), dest.getHeight()
    };
    this->asignarColores(color);
    SDL_RenderCopy(this->renderer, this->textura, &sdlSrc, &sdlFin);
}

void SdlTexto::renderFijo(const Area& dest, int color) {
    SDL_Rect sdlSrc = {0, 0, 1024, 768};
    SDL_Rect sdlFin = {
        dest.getX(), dest.getY(),
        dest.getWidth(), dest.getHeight()
    };
    this->asignarColores(color);
    SDL_RenderCopy(this->renderer, this->textura, &sdlSrc, &sdlFin);
}

SdlTexto::~SdlTexto() {
    SDL_DestroyTexture(this->textos);

    TTF_CloseFont(this->fuente);
}

void SdlTexto::asignarColores(int color) {
    switch (color) {
        case 0:
            SDL_SetTextureColorMod(this->textura, BLANCO);
            break;
        case 1:
            SDL_SetTextureColorMod(this->textura, ROJO);
            break;
        case 2:
            SDL_SetTextureColorMod(this->textura, CELESTE);
            break;
        case 3:
            SDL_SetTextureColorMod(this->textura, VERDE);
            break;
        case 4:
            SDL_SetTextureColorMod(this->textura, AMARILLO);
            break;
        case 5:
            SDL_SetTextureColorMod(this->textura, AZUL);
            break;
        case 6:
            SDL_SetTextureColorMod(this->textura, FUCSIA);
            break;        
    }
}

void SdlTexto::renderMain() {
    SDL_Rect sdlSrc = {0, 0, 1024, 768};
    SDL_Rect sdlDest = {400, 400, 200, 100};
    SDL_RenderCopy(this->renderer, this->textura, &sdlSrc, &sdlDest);
}

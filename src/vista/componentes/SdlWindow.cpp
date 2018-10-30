#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_mixer.h>
#include "SdlException.h"
#include "SdlWindow.h"
#include <iostream>

SdlWindow* SdlWindow::sInstance = nullptr;
bool SdlWindow::sInitialize = false;

SdlWindow::SdlWindow(){   
    int errCode = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    if (errCode) {
        throw SdlException("Error en la inicialización", SDL_GetError());
    }
    this->window = SDL_CreateWindow("Worms",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,
            width,height,SDL_WINDOW_SHOWN);
    if(this->window == NULL){
        throw SdlException("Error al crear ventana", SDL_GetError());
    }
    
    this->renderer = SDL_CreateRenderer(this->window,-1,SDL_RENDERER_ACCELERATED);
    if(this->renderer == NULL){
        throw SdlException("Error al crear el rendered", SDL_GetError());
    }
    sInitialize = true;
}

SdlWindow* SdlWindow::instance(){        
    if(!sInitialize){       
        sInstance = new SdlWindow();
    }
    return sInstance;
}

void SdlWindow::release(){
    delete sInstance;
    sInstance = nullptr;
    
    sInitialize = false;
}

bool SdlWindow::inicializado(){
    return sInitialize;
}

SdlWindow::~SdlWindow() {    
    if (this->renderer) {
        SDL_DestroyRenderer(this->renderer);
        this->renderer = nullptr;
    }

    if (this->window) {
        SDL_DestroyWindow(this->window);
        this->window = nullptr;
    }
}

void SdlWindow::fill(int r, int g, int b, int alpha) {
    SDL_SetRenderDrawColor(this->renderer,
                           r, g, b, alpha);
    SDL_RenderClear(this->renderer);
}

void SdlWindow::fill() {
    this->fill(0x33,0x33,0x33,0xFF);
}

void SdlWindow::mostrarFondo(){        
    this->texture->renderMain();
}

void SdlWindow::render() {    
    SDL_RenderPresent(this->renderer);
}

void SdlWindow::setTextura(std::shared_ptr<SdlTexture> textura) {
    this->texture = textura;
}

SDL_Renderer* SdlWindow::getRenderer() const {
    return this->renderer;
}
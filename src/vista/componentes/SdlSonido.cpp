#include <SDL2/SDL.h>
#include <iostream>

#include "SdlSonido.h"

#include "SdlException.h"

SdlSonido::SdlSonido(std::string ruta, std::string tipo) : music(NULL),
        efecto(NULL){    
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {        
        throw SdlException("Error al abrir el audio", Mix_GetError());
    }    
    if(tipo != "mp3"){
        this->efecto = this->getEfecto(ruta);
        Mix_VolumeChunk(this->efecto,128);
    }else{
        this->music = this->getMusica(ruta);        
        Mix_VolumeMusic(10);
    }
}

Mix_Music* SdlSonido::getMusica(std::string nombreArch) {
    this->music = Mix_LoadMUS(nombreArch.c_str());
    if (!this->music) {
        throw SdlException("Error al cargar la musica", Mix_GetError());
    }
    return this->music;
}

Mix_Chunk* SdlSonido::getEfecto(std::string nombreArch) {
    this->efecto = Mix_LoadWAV(nombreArch.c_str());
    if (!this->efecto) {
        throw SdlException("Error al cargar SFX", Mix_GetError());
    }

    return this->efecto;
}

void SdlSonido::playMusic() {
    Mix_PlayMusic(this->music, 100);
}


void SdlSonido::play(){
    if(this->efecto != NULL){
        this->playEfecto();
    }else{
        this->playMusic();
    }        
}

void SdlSonido::pauseMusica() {
    if (Mix_PlayingMusic() != 0) {
        Mix_PauseMusic();
    }
}

void SdlSonido::resumeMusica() {
    if (Mix_PausedMusic() != 0) {
        Mix_ResumeMusic();
    }
}

void SdlSonido::playEfecto() {
    Mix_PlayChannel(MIX_DEFAULT_CHANNELS, this->efecto, 0);
}

SdlSonido::~SdlSonido() {
    Mix_CloseAudio();
}


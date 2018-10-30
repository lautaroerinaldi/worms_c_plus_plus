#ifndef SDLSONIDOS_H
#define SDLSONIDOS_H

#include <string>
#include <SDL2/SDL_mixer.h>

class SdlSonido {
private:
    Mix_Music* music;
    Mix_Chunk* efecto;
    
public:
    //constructor del sonido
    SdlSonido(std::string ruta, std::string tipo);
    
    //devuelve la musica cargada
    Mix_Music* getMusica(std::string nombreArch);    
    
    //devuelve un efecto cargado
    Mix_Chunk* getEfecto(std::string nombreArch);
    
    //play
    void play();
    
    //play de la musica
    void playMusic();
    
    //pausa la musica
    void pauseMusica();
    
    //reanuda la musica
    void resumeMusica();
    
    //play del efecto
    void playEfecto();
    
    //destructor del sonido
    ~SdlSonido();
};

#endif /* SDLSONIDOS_H */


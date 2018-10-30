#ifndef SDLTEXTO_H
#define SDLTEXTO_H

#include <string>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_render.h>
#include "SdlException.h"
#include "SdlWindow.h"
#include "../elementos/SdlCamara.h"
#include <map>
#include "Area.h"

class SDL_Renderer;
class SdlWindow;

class SdlTexto {
private:
    SDL_Texture* createTextTexture(TTF_Font* font,std::string text);
    TTF_Font* fuente;
    SDL_Texture* textos;
    SDL_Texture* textura;
    int textureAncho; 
    int textureAlto;
    SDL_Renderer* renderer;
    SdlCamara &camara;
    
public:
    //Crea un SDL_Texto para mostrar texto    
    SdlTexto(const std::string &text,const std::string &fontPath,int size,
                                                             SdlCamara &camara);           
    
    //devuelve la textura generada por la fuente
    SDL_Texture* getText(std::string text, std::string nombreArch, int size);
    
    
    //devuelve la fuente
    TTF_Font* getFont(std::string nombreFont, int size);
    
    //renderiza la textura de texto
    void render(const Area& dest,int color);

    //renderiza la textura de texto en una posicion fija
    void renderFijo(const Area& dest,int color);
    
    //renderiza la pantalla principal
    void renderMain() ;
    
    //asigna los colores a los demas jugadores
    void asignarColores(int color);
    
    //destructor del texto
    ~SdlTexto();

};

#endif /* SDLTEXTO_H */


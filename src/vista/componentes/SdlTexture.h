#ifndef SDL_TEXTURE_H
#define SDL_TEXTURE_H

#include <string>
#include <SDL2/SDL_render.h>

#include "SdlWindow.h"
#include "../elementos/SdlCamara.h"


class SDL_Texture;
class SDL_Renderer;
class SdlWindow;
class Area;

class SdlTexture {
private:
    SDL_Texture* loadTexture(const std::string &filename);
    SDL_Renderer* renderer;
    std::string nombreSprite;
    SDL_Texture* texture;
    SdlCamara &camara;

public:
    //Crea un SDL_Texture de imagen, lanza una excepción si el filename es inválido
    SdlTexture(const std::string &filename, const SdlWindow& window,
                                                            SdlCamara &camara);    
            
    //Renderiza la textura cargada
    int render(const Area& src, const Area& dest,
               int angulo, SDL_RendererFlip flip,int color);
    
    //Renderiza la textura cargada en un lugar fijo
    int renderFijo(const Area& src, const Area& dest,
               int angulo, SDL_RendererFlip flip,int color);

    //renderiza la pantalla principal
    int renderMain() const;

    //Retorna la textura
    SDL_Texture* getTextura();

    //dibuja la imagen
    int dibujar(Area &dest,int grado);

    //devuelve el nombre de la textura
    std::string getNombreTextura() const;
            
    //asigna los colores a los demas jugadores
    void asignarColores(int color);
    
    //Libera la memoria reservada por la textura
    ~SdlTexture();
};

#endif

#ifndef SDL_WINDOW_H
#define SDL_WINDOW_H

#include "Area.h"
#include "SdlTexture.h"
#include <memory>

class SDL_Window;
class SDL_Renderer;
class SdlTexture;

class SdlWindow {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;        
    std::shared_ptr<SdlTexture> texture;    
    static SdlWindow* sInstance;
    static bool sInitialize;
    
    //dimension del mapa
    const int widthMapa = 1000; 
    const int heightMapa = 1000;
    
    //dimension de la camara
    int width = 1000;
    int height = 700;       
    
public:
    //constructor de la ventana    
    SdlWindow();
    
    //destructor de la ventana
    ~SdlWindow();
    
    //creo la instancia a traves del patron singleton
    static SdlWindow* instance();   
    
    //elimino la instancia creada
    static void release();
    
    //consulta si la ventana ya esta inicializada
    static bool inicializado();
    
    //renderiza el fondo que lleva la ventana
    void mostrarFondo();
    
    //seteo la textura que sera el fondo
    void setTextura(std::shared_ptr<SdlTexture> textura);
    
    //llama al fill
    void fill();
    
    //llena el fill con los colores pasados por parametros y la ocuridad de alpha
    void fill(int r, int g, int b, int alpha);
    
    //renderiza la ventaa
    void render();
    
    //devuelve el renderer de la ventana
    SDL_Renderer* getRenderer() const;
};

#endif

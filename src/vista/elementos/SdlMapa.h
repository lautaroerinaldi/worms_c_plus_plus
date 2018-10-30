#ifndef SDLMAPA_H
#define SDLMAPA_H

#include <vector>
#include <map>
#include <memory>

#include "../../comun/Protocolo/Balas/ImpactarBala.h"
#include "../../comun/Protocolo/Balas/MoverBala.h"
#include "../estadosGusanos/State.h"
#include "../componentes/SdlWindow.h"
#include "../componentes/SdlTexture.h"
#include "SdlViga.h"
#include "SdlGusano.h"
#include "SdlBala.h"

class SdlMapa {
private:
    std::vector<SdlViga> vigas;
    std::map<int, SdlGusano> gusanos;
    std::vector<std::shared_ptr<SdlTexture>> fondos;    
    std::map<int, SdlBala> balas;
    static SdlMapa* sInstance;
    static bool sInitialize;

public:
    //constructor del mapa    
    SdlMapa();

    //instancio el mapa con el patron singleton
    static SdlMapa* instance();
    
    //elimino la instancia
    static void release();
    
    //consulta si el mapa ya esta inicializado
    static bool inicializado();

    //agrega una viga al mapa
    void agregarViga(SdlViga &viga);

    //agrega un gusano al mapa
    void agregarGusano(SdlGusano &gusano, int id);
    
    //agrega una bala al mapa
    void agregarBala(SdlBala &bala, int id);

    //renderiza el mapa
    void render(std::map<std::string, std::shared_ptr<SdlTexto>> &textos);

    //agregar un elemento de fondo fijo
    void agregarFondo(std::shared_ptr<SdlTexture> fondo);

    //devuelve un punturo del gusano que le corresponda al turno
    SdlGusano* getGusano(int idGusano);
    
    //verifica si un gusano murio y lo elimina del mapa
    void verificarMuertes();
    
    //mueve la bala en el mapa
    void moverProyectil(MoverBala movBala);
    
    //impacta el Proyectil
    void impactarProyectil(ImpactarBala impacto);
    
    //destruye el proyectil del mapa
    void destruirProyectil(int id);
    
    //proyectil es santa
    bool proyectilEsSanta(int idProyectil);
    
    //llama al destructor del mapa    
    virtual ~SdlMapa();
};

#endif


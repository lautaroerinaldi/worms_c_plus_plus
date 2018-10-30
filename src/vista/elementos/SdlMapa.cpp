#include <iostream>
#include <stdexcept>

#include "SdlMapa.h"
#include "../../comun/Codigos.h"
#include "../CodigosVista.h"

SdlMapa* SdlMapa::sInstance = nullptr;
bool SdlMapa::sInitialize = false;


SdlMapa::SdlMapa() {
    sInitialize = true;    
}


void SdlMapa::agregarGusano(SdlGusano& gusano, int id) {
    this->gusanos.insert(std::pair<int, SdlGusano>(id, std::move(gusano)));
}

void SdlMapa::agregarBala(SdlBala& bala, int id){
    this->balas.insert(std::pair<int, SdlBala>(id,std::move(bala)));
}


void SdlMapa::agregarViga(SdlViga& viga) {
    this->vigas.push_back(std::move(viga));
}


void SdlMapa::agregarFondo(std::shared_ptr<SdlTexture> fondo) {
    this->fondos.push_back(fondo);
}


void SdlMapa::render(std::map<std::string, std::shared_ptr<SdlTexto>> &textos) {
    Area srcArea(0, 0, 1024, 768);
    Area destAreaAgua(0, ALTO_MAPA - FACTOR_ESCALA_DE_MODELO_A_VISTA, 
                                   ANCHO_MAPA, FACTOR_ESCALA_DE_MODELO_A_VISTA);    
    for (size_t i = 0; i < this->fondos.size(); i++) {        
        this->fondos[i]->render(srcArea, destAreaAgua,0, SDL_FLIP_NONE, -1);             
    }    
    
    for (size_t i = 0; i < this->vigas.size(); i++) {
        this->vigas[i].dibujar();
    }
    
    std::map<int, SdlGusano>::iterator it;
    for (it = gusanos.begin(); it != gusanos.end(); it++) {
        it->second.animar(textos);
    }
    
    std::map<int,SdlBala>::iterator itBala;
    for(itBala = this->balas.begin(); itBala != this->balas.end(); itBala++){
        itBala->second.dibujar();
    }
}


SdlMapa* SdlMapa::instance(){        
    if(!sInitialize){       
        sInstance = new SdlMapa();
    }
    return sInstance;
}


void SdlMapa::release(){
    delete sInstance;
    sInstance = nullptr;
    
    sInitialize = false;
}


bool SdlMapa::inicializado(){
    return sInitialize;
}


SdlGusano* SdlMapa::getGusano(int idGusano) {
    SdlGusano *gusano;
    auto search = this->gusanos.find(idGusano);
    if(search != this->gusanos.end()){
        gusano = &this->gusanos.at(idGusano);
        return gusano;
    }
    gusano = nullptr;
    return gusano;
}

void SdlMapa::verificarMuertes(){
    std::map<int, SdlGusano>::iterator it = this->gusanos.begin();
    while(it != this->gusanos.end())
        if(!it->second.getVida())
            it = this->gusanos.erase(it);
        else
            ++it;
}

void SdlMapa::moverProyectil(MoverBala movBala){
    auto search = this->balas.find(movBala.getIdBala());
    if(search != this->balas.end()){
            this->balas.at(movBala.getIdBala()).mover(movBala.getXVista(),
                            movBala.getYVista(),movBala.getAnguloEnGrados());
    }
}

void SdlMapa::impactarProyectil(ImpactarBala impacto){
    auto search = this->balas.find(impacto.getIdBala());
    if(search != this->balas.end()){
        this->balas.at(impacto.getIdBala()).impactar(impacto.getRadioVista());
    }
}


void SdlMapa::destruirProyectil(int id) {
    auto search = this->balas.find(id);
    if(search != this->balas.end()){
        this->balas.erase(id);
    }    
}


bool SdlMapa::proyectilEsSanta(int idProyectil){
    auto search = this->balas.find(idProyectil);
    if(search != this->balas.end()){
        return this->balas.at(idProyectil).getTipo() == GRANADA_SANTA;
    }    
    return false;    
}


SdlMapa::~SdlMapa() {
}


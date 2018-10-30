#include "SdlInformacion.h"

#include <string>
#include <iostream>

SdlInformacion::SdlInformacion() :  srcBorde(0, 0, 50, 30), 
                srcArea(0, 0, 1024, 768), tiempoRestante(0), potencia(0),
                mostrarPotencia(false), viento(0), mostrarViento(false),
                tiempoArma(5),mostrarTiempoArma(false),turnoJugador(0),
                numeroJugador(0){
}

void SdlInformacion::actualizarTiempoRestante(int tiempo) {
    this->tiempoRestante = tiempo;
}

void SdlInformacion::render(std::map<std::string, std::shared_ptr<SdlTexto>>
        &textos) {
    textos.at(std::to_string(this->tiempoRestante))->renderFijo(srcBorde, 0);
    if (this->mostrarPotencia) {
        Area srcTextoPotencia(0, 30, 100, 20);
        Area srcPotencia(100, 30, 50, 20);
        textos.at("potencia")->renderFijo(srcTextoPotencia, 0);
        textos.at(std::to_string(this->potencia))->renderFijo(srcPotencia, 0);
    }
    if (this->mostrarViento) {
        this->dibujarViento(textos);
    }
    if(this->mostrarTiempoArma){
        Area srcTextoTiempoArma(0, 50, 100, 20);
        Area srcTiempoArma(100, 50, 50, 20);
        textos.at("conteo")->renderFijo(srcTextoTiempoArma, 0);
        textos.at(std::to_string(this->tiempoArma))->renderFijo(srcTiempoArma, 0);
    }
    if(this->turnoJugador){
        Area srcTextoJugador(400, 0, 150, 20);
        Area srcTurnoJugador(550, 0, 25, 20);
        textos.at("jugador")->renderFijo(srcTextoJugador, 0);
        textos.at(std::to_string(this->turnoJugador))->
                                                renderFijo(srcTurnoJugador, 0);
    }
    if(this->numeroJugador){
        Area srcTextonumeroJugador(800, 0, 150, 20);
        Area srcNumeroJugador(950, 0, 25, 20);
        textos.at("numeroJugador")->renderFijo(srcTextonumeroJugador, 0);
        textos.at(std::to_string(this->numeroJugador))->
                                                renderFijo(srcNumeroJugador, 0);        
    }
}

void SdlInformacion::dibujarViento(std::map<std::string,
    std::shared_ptr<SdlTexto>> &textos) {
    float vientoF = this->viento / 100;
    int vientoParteEntera = (int) vientoF;
    int vientoParteDecimal = this->viento - (vientoParteEntera * 100);
    Area srcTextoViento(675, 680, 80, 20);
    Area srcVientoParteEnteraC(755, 680, 30, 20);
    Area srcVientoParteEntera2(770, 680, 15, 20);
    Area srcPunto(785, 680, 5, 20);
    Area srcVientoParteDecimal(790, 680, 30, 20);
    Area srcMetrosPorSegundo(820, 680, 50, 20);
    Area srcImagen(870, 680, 120, 20);    
    textos.at("viento")->renderFijo(srcTextoViento, 0);
    if(vientoParteEntera > 9){
        textos.at(std::to_string(vientoParteEntera))->renderFijo(srcVientoParteEnteraC, 0);    
    }else{
        textos.at(std::to_string(vientoParteEntera))->renderFijo(srcVientoParteEntera2, 0);
    }
    
    textos.at("punto")->renderFijo(srcPunto, 0);
    textos.at(std::to_string(vientoParteDecimal))->renderFijo(srcVientoParteDecimal, 0);
    textos.at("ms")->renderFijo(srcMetrosPorSegundo, 0);   
    Area sdlSrc(0, 0, 1024, 768);
    this->texturaViento->renderFijo(sdlSrc,srcImagen, 0, SDL_FLIP_NONE ,0);
}

void SdlInformacion::deshabilitarPotencia() {
    this->mostrarPotencia = false;
}

void SdlInformacion::mostrarValorPotencia(int potencia) {
    this->potencia = potencia;
}

void SdlInformacion::habilitarPotencia() {
    this->mostrarPotencia = true;
}

void SdlInformacion::setViento(int viento) {
    this->viento = viento;
}

void SdlInformacion::setTexturaViento(std::shared_ptr<SdlTexture> &texturaViento) {
    this->texturaViento = texturaViento;
    this->mostrarViento = true;
}

void SdlInformacion::habilitarTiempoDelArma(){
    this->mostrarTiempoArma = true;
}

void SdlInformacion::deshabilitarTiempoDelArma(){
    this->mostrarTiempoArma = false;
}

void SdlInformacion::setTiempoDelArma(int tiempo){
    this->tiempoArma = tiempo;
}

void SdlInformacion::actualizarTurno(int jugador){
    this->turnoJugador = jugador;
}

void SdlInformacion::setNumeroJugador(int numeroJugador){
    this->numeroJugador = numeroJugador;
}

SdlInformacion::~SdlInformacion() {
}


#include <iostream>
#include <string>
#include "SdlGusano.h"
#include "../../comun/Codigos.h"


#define ESPACIO_VIDA_GUSANO 20

SdlGusano::SdlGusano(int id, Area &area, int color, int vida, std::shared_ptr<State> estado) :
id(id), posicion(std::move(area)), color(color), vida(vida),
estado(estado), direccion(IZQUIERDA), inclinacion(NORMAL){
}

void SdlGusano::animar(std::map<std::string, std::shared_ptr<SdlTexto>> &textos) {
    this->estado->render(this->posicion, this->direccion, this->color);
    auto search = textos.find(std::to_string(this->vida));
    if (search != textos.end()) {
        Area areaTexto(this->posicion.getX(),
                this->posicion.getY() - ESPACIO_VIDA_GUSANO,
                25, 20);
        textos.at(std::to_string(this->vida))->render(areaTexto,this->color);       
    }
}


void SdlGusano::render() {
    //    this->estado->render();
}


void SdlGusano::setEstado(std::shared_ptr<State> estado) {
    this->estado = estado;
}


int SdlGusano::handle(const std::string &nombreSprite) {
    return estado->Handle(nombreSprite);
}


Area SdlGusano::getPosicion() {
    return this->posicion;
}

void SdlGusano::setPosicion(Area &posicion) {
    this->posicion = posicion;
}

int SdlGusano::getDireccion() {
    return this->direccion;
}


void SdlGusano::setDireccion(int direccion) {
    this->direccion = direccion;
}


int SdlGusano::getInclinacion() {
    return this->inclinacion;
}

void SdlGusano::setInclinacion(int inclinacion) {
    this->inclinacion = inclinacion;
}

void SdlGusano::mover(int x, int y) {
    Area area(x, y, TAM_GUSANO * MULTIPLICAR_VISTA,
            TAM_GUSANO * MULTIPLICAR_VISTA);
    this->setPosicion(area);
    this->estado->mover(x);
}

int SdlGusano::getId() {
    return this->id;
}

SdlArma* SdlGusano::getArma() {
    return &this->arma;
}

void SdlGusano::setArma(int arma) {
    this->arma.setTipo(arma);
}

void SdlGusano::actualizarPunteria(int direccionDeLaPunteria) {
    this->estado->mover(direccionDeLaPunteria);
}

int SdlGusano::direccionar(int direccion) {
    int res = this->estado->direccionar();
    if (res == 2) {
        res = !(this->direccion == direccion);
    }
    return res;
}

int SdlGusano::puedeAtacar() {
    return this->estado->puedeAtacar();
}

int SdlGusano::getAngulo() {
    return this->estado->getAngulo();
}

int SdlGusano::getVida() {
    return this->vida;
}

void SdlGusano::setVida(int vida) {
    this->vida = vida;
}

SdlGusano::~SdlGusano() {
}


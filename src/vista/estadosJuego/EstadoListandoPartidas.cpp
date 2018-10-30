#include <iostream>

#include "EstadoListandoPartidas.h"

#define POSICION1 370

#define DIFERENCIA 60

EstadoListandoPartidas::EstadoListandoPartidas(SdlJuego *juego, SdlCamara &camara) :
juego(juego), camara(camara), areaPuntero(250, 365, 50, 50) {    
    this->partidas = this->juego->getPartidas();
    this->cargarTextosPartidas();
    this->cantidad = this->partidas.size();
    this->posPuntero = 0;
}

int EstadoListandoPartidas::Handle(Uint32 &evento) {
    switch (evento) {
        case SDL_KEYDOWN:
        {
            SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) evento;
            switch (keyEvent.keysym.sym) {
                case SDLK_UP:
                    if (this->posPuntero > 0) {
                        this->areaPuntero.setY(this->areaPuntero.getY()
                                - DIFERENCIA);
                        this->posPuntero--;
                    }
                    break;
                case SDLK_DOWN:
                    if (this->posPuntero < this->cantidad) {
                        this->areaPuntero.setY(this->areaPuntero.getY()
                                + DIFERENCIA);
                        this->posPuntero++;
                    }
                    break;
                case 13:
                    this->realizoSeleccion();
                    break;
            }
        }
            break;
        case SDL_QUIT:
            return 0;
            break;
    }
    return 1;
}

void EstadoListandoPartidas::render(std::map<std::string, std::shared_ptr<SdlTexture>> &texturas,
        std::map<std::string, std::shared_ptr<SdlTexto>> &textos) {

    Area areaHeader(0, 0, 1200, 200);
    Area areaSeleccionar(5, 200, 500, 100);
    Area areaPartida(300, 300, 200, 60);
    Area areaNombreEscenario(600, 300, 350, 60);
    Area areaAnterior(300, 300, 200, 60);


    texturas.at("header")->dibujar(areaHeader, 0);
    texturas.at("puntero")->dibujar(this->areaPuntero, 0);
    textos.at("seleccionarPartida")->render(areaSeleccionar, 1);
    textos.at("partida")->render(areaPartida, 4);
    textos.at("escenario")->render(areaNombreEscenario, 4);


    std::map<int, std::string>::iterator it;
    for (it = this->partidas.begin(); it != this->partidas.end(); ++it) {
        Area areaPartida(areaAnterior.getX() + 80, areaAnterior.getY() + 60,
                areaAnterior.getWidth() - 180, areaAnterior.getHeight() - 10);
        textoPartidas.at(std::to_string(it->first))->render(areaPartida, 3);

        Area areaEscenario(areaAnterior.getX() + 320, areaAnterior.getY() + 60,
                areaAnterior.getWidth(), areaAnterior.getHeight() - 5);
        textoPartidas.at(it->second)->render(areaEscenario, 3);
        Area areaActualizada(areaAnterior.getX(), areaAnterior.getY() + 60,
                areaAnterior.getWidth(), areaAnterior.getHeight());
        areaAnterior = areaActualizada;
    }

    Area areaVolver(areaAnterior.getX() + 30, areaAnterior.getY() + 60,
            areaAnterior.getWidth() + 150, areaAnterior.getHeight());
    textos.at("volver")->render(areaVolver, 2);
}

void EstadoListandoPartidas::realizoSeleccion() {
    if (this->posPuntero == this->cantidad) {
        this->juego->setEstado(PANTALLA_PRINCIPAL);
    } else {
        std::map<int, std::string>::iterator it;
        it = this->partidas.begin();
        int aux = this->posPuntero;
        while (aux) {
            aux--;
            it++;
        }
        this->juego->seleccionPartida(it->first);
        std::cout << "seleccionaste: " << it->second << std::endl;
    }
}

void EstadoListandoPartidas::cargarTextosPartidas() {
    std::map<int, std::string>::iterator it;
    for (it = this->partidas.begin(); it != this->partidas.end(); ++it) {
        this->textoPartidas.insert(std::make_pair(std::to_string(it->first),
                (std::shared_ptr<SdlTexto>) new SdlTexto(
                std::to_string(it->first), "font/Roboto-Medium.ttf", 50,
                this->camara)));
        this->textoPartidas.insert(std::make_pair(it->second,
                (std::shared_ptr<SdlTexto>) new SdlTexto(
                it->second, "font/Roboto-Medium.ttf", 50, this->camara)));
    }
}

EstadoListandoPartidas::~EstadoListandoPartidas() {
}



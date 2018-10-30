#include "EstadoListandoJugadores.h"

#define POSICIONJUG2 320
#define POSICIONJUG3 400
#define POSICIONJUG4 480
#define MENUPPAL 560
#define DIFERENCIA 80

EstadoListandoJugadores::EstadoListandoJugadores(SdlJuego *juego) :
juego(juego), areaPuntero(300, 320, 50, 50) {
}

int EstadoListandoJugadores::Handle(Uint32 &evento) {
    switch (evento) {
        case SDL_KEYDOWN:
        {
            SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) evento;
            switch (keyEvent.keysym.sym) {
                case SDLK_UP:
                    if (this->areaPuntero.getY() != POSICIONJUG2) {
                        this->areaPuntero.setY(this->areaPuntero.getY()
                                                                - DIFERENCIA);
                    }
                    break;
                case SDLK_DOWN:
                    if (this->areaPuntero.getY() != MENUPPAL) {
                        this->areaPuntero.setY(this->areaPuntero.getY()
                                                                + DIFERENCIA);
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

void EstadoListandoJugadores::render(std::map<std::string, std::shared_ptr<SdlTexture>> &texturas,
        std::map<std::string, std::shared_ptr<SdlTexto>> &textos) {

    Area areaHeader(0, 0, 1200, 200);

    Area areaSeleccionar(5, 200, 500, 100);
    Area areaJugador2(400, 300, 200, 80);
    Area areaJugador3(400, 380, 200, 80);
    Area areaJugador4(400, 460, 200, 80);
    Area areaVolver(400, 540, 350, 80);

    texturas.at("header")->dibujar(areaHeader, 0);
    texturas.at("puntero")->dibujar(this->areaPuntero, 0);
    textos.at("seleccionarJugadores")->render(areaSeleccionar, 1);
    textos.at("2jugadores")->render(areaJugador2, 2);
    textos.at("3jugadores")->render(areaJugador3, 2);
    textos.at("4jugadores")->render(areaJugador4, 2);
    textos.at("volver")->render(areaVolver, 2);
}

void EstadoListandoJugadores::realizoSeleccion(){
    switch(this->areaPuntero.getY()){
        case POSICIONJUG2:
            this->juego->setCantidadDeJugadores(2);            
            this->juego->setEstado(LISTANDO_ESCENARIOS);
            break;
        case POSICIONJUG3:
            this->juego->setCantidadDeJugadores(3);
            this->juego->setEstado(LISTANDO_ESCENARIOS);
            break;
        case POSICIONJUG4:
            this->juego->setCantidadDeJugadores(4);
            this->juego->setEstado(LISTANDO_ESCENARIOS);
            break;
        case MENUPPAL:
            this->juego->setEstado(PANTALLA_PRINCIPAL);
            break;
    }
}

EstadoListandoJugadores::~EstadoListandoJugadores() {
}


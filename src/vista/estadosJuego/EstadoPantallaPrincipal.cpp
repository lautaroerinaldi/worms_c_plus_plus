#include "EstadoPantallaPrincipal.h"
#include "EstadoListandoJugadores.h"

#define POSICIONCREAR 270
#define POSICIONUNIRSE 370

EstadoPantallaPrincipal::EstadoPantallaPrincipal(SdlJuego *juego) :
                juego(juego),areaPuntero(300, 270, 50, 50) {
    this->juego->setCantidadDeJugadores(0);
}

int EstadoPantallaPrincipal::Handle(Uint32 &evento) {
    switch (evento) {
        case SDL_KEYDOWN:
        {
            SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) evento;
            switch (keyEvent.keysym.sym) {
                case SDLK_UP:
                    this->areaPuntero.setY(POSICIONCREAR);
                    break;
                case SDLK_DOWN:
                    this->areaPuntero.setY(POSICIONUNIRSE);
                    break;
                case 13:
                    if (areaPuntero.getY() == POSICIONCREAR) {
                        this->juego->setEstado(LISTANDO_JUGADORES);
                    }
                    if (areaPuntero.getY() == POSICIONUNIRSE){
                        this->juego->setEstado(LISTANDO_PARTIDAS);
                    }
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

void EstadoPantallaPrincipal::render(std::map<std::string, std::shared_ptr<SdlTexture>> &texturas,
        std::map<std::string, std::shared_ptr<SdlTexto>> &textos) {

    Area areaCrear(400, 250, 200, 100);
    Area areaUnirse(400, 350, 300, 100);
    Area areaHeader(0, 0, 1200, 200);
    Area areaAnio(250, 520, 500, 80);
    Area areaCreador1(50, 620, 300, 80);
    Area areaCreador2(350, 620, 300, 80);
    Area areaCreador3(650, 620, 300, 80);

    texturas.at("header")->dibujar(areaHeader, 0);
    texturas.at("puntero")->dibujar(this->areaPuntero, 0);
    textos.at("crear")->render(areaCrear, 2);
    textos.at("unirse")->render(areaUnirse, 2);
    textos.at("anio")->render(areaAnio, 1);
    textos.at("creador1")->render(areaCreador1, 1);
    textos.at("creador2")->render(areaCreador2, 1);
    textos.at("creador3")->render(areaCreador3, 1);
}

EstadoPantallaPrincipal::~EstadoPantallaPrincipal() {
}


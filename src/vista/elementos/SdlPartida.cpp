#include <SDL2/SDL.h>
#include <iostream>
#include <exception>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_messagebox.h>
#include <unistd.h>
#include <memory>
#include <dirent.h>
#include <locale>
#include <string>

#include "SdlPartida.h"
#include "../eventos/SdlProcesadorDeEventos.h"
#include "../componentes/SdlTexture.h"
#include "../estadosGusanos/EstadoAnimandoFijo.h"
#include "../estadosGusanos/EstadoMoviendo.h"
#include "../estadosGusanos/EstadoCargandoArma.h"
#include "../estadosGusanos/EstadoApuntando.h"
#include "../estadosGusanos/EstadoAtacando.h"
#include "../estadosGusanos/EstadoMuriendo.h"
#include "../estadosJuego/EstadoPantallaFinalizada.h"
#include "../../comun/Codigos.h"
#include "../CodigosVista.h"
#include "../../comun/Utiles/Tiempo.h"

#define ALTO_VIGA (ALTURA_VIGA * FACTOR_ESCALA_DE_MODELO_A_VISTA / ESCALAR_CONSTANTES)
#define MAX_VIDA_GUSANO 300

SdlPartida::SdlPartida(Destinatario * cliente) :
cliente(cliente), running(true) {
    this->init();
}

void SdlPartida::init() {
    this->window = SdlWindow::instance();
    if (!SdlWindow::inicializado()) {
        this->running = false;
    }
    this->cargarTodo();
    this->window->setTextura(this->texturas["fondoWorms"]);
    this->mapa = SdlMapa::instance();
    this->crearFondo();
    this->window->fill();
    this->partidaFinalizada = false;
    this->soyGanador = false;
}

int SdlPartida::crearViga(CrearViga crearViga) {
    Area area(crearViga.getX(), crearViga.getY(), crearViga.getLongitud(), ALTO_VIGA);
    SdlViga viga(area, this->texturas["viga0"], crearViga.getAnguloEnGrados());
    this->mapa->agregarViga(viga);
    return 0;
}

int SdlPartida::crearGusano(CrearGusano crearGusano) {
    Area area(crearGusano.getX(), crearGusano.getY(),
            TAM_GUSANO * MULTIPLICAR_VISTA,
            TAM_GUSANO * MULTIPLICAR_VISTA);
    std::string nombreTextura = QUIETO_STR
            + std::to_string(crearGusano.getInclinacion());
    std::shared_ptr<State> estado(
            new EstadoAnimandoFijo(this->texturas[nombreTextura]));
    SdlGusano gusano(crearGusano.getIdGusano(), area,
            crearGusano.getIdJugador(), crearGusano.getVida(),
            std::move(estado));
    this->mapa->agregarGusano(gusano, crearGusano.getIdGusano());
    return 0;
}

void SdlPartida::crearBala(CrearBala crearBala) {    
    Area area(crearBala.getXVista(), crearBala.getYVista(),
            TAM_BALA * MULTIPLICAR_VISTA,
            TAM_BALA * MULTIPLICAR_VISTA);
    std::string nombreSprite = "bala" + std::to_string(crearBala.getTipoArma());
    std::string explosion = "explosion50";    
    auto search = this->texturas.find(nombreSprite);
    if (search != this->texturas.end()) {
        SdlBala bala(area, this->texturas[nombreSprite],
                crearBala.getAnguloEnGrados(), this->texturas[explosion],
                crearBala.getTipoArma());
        this->mapa->agregarBala(bala, crearBala.getIdBala());
        this->camara.activarSeguirBala();
    }
}

int SdlPartida::crearFondo() {
    this->mapa->agregarFondo(this->texturas["agua"]);
    return 0;
}

void SdlPartida::iniciarTurno(IniciarTurno turno) {
    this->gusanoEnTurno = this->mapa->getGusano(turno.getIdGusano());
    this->jugador = turno.getIdJugador();
    if (!this->gusanoEnTurno) {
        throw std::runtime_error("no existe el id del gusano");
    }
    std::string nombreTextura = "seleccionar"
            + std::to_string(this->gusanoEnTurno->getInclinacion());
    std::shared_ptr<State> estado(
            new EstadoAnimandoFijo(this->texturas[nombreTextura]));
    this->gusanoEnTurno->setEstado(estado);
    this->informacionDeCliente.actualizarTurno(this->jugador);
    this->sonidos.at("StartRound")->play();
    this->camara.seguirGusano(this->gusanoEnTurno->getPosicion().getX(),
            this->gusanoEnTurno->getPosicion().getY());
}

void SdlPartida::finalizarTurno(FinalizarTurno finTurno) {
    std::string nombreTextura = QUIETO_STR
            + std::to_string(this->gusanoEnTurno->getInclinacion());
    std::shared_ptr<State> estado(
            new EstadoAnimandoFijo(this->texturas[nombreTextura]));
    this->gusanoEnTurno->setEstado(estado);
    this->gusanoEnTurno->setArma(-1);
    this->mapa->verificarMuertes();
    this->informacionDeCliente.deshabilitarTiempoDelArma();
}

void SdlPartida::run() {
    try {
        SdlProcesadorDeEventos procesador(cliente);
        SDL_Event event;
        this->sonidos.at("ambiente")->play();
        EstadoPantallaFinalizada pantallaFinalizada(this->texturas, this->textos);
        this->informacionDeCliente.setNumeroJugador(this->cliente->getIdJugador());
        while (this->running) {
            Tiempo tiempo(TIEMPO_ESPERA_EN_MICROSEGUNDOS);
            this->window->mostrarFondo();
            while (SDL_PollEvent(&event) != 0) {
                this->running = procesador.procesarEvento(event.type, this,
                        this->gusanoEnTurno, this->sonidos,
                        this->informacionDeCliente, this->camara);
            }
            if (partidaFinalizada) {
                pantallaFinalizada.mostrarPantalla(this->soyGanador);
            } else {
                this->mapa->render(this->textos);
                this->informacionDeCliente.render(this->textos);
            }
            this->window->render();
        }
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    this->window->release();
    this->cliente->apagar();
}

void SdlPartida::cargarTodo() {
    std::shared_ptr<SdlTexture> texturaCargando(
            new SdlTexture("img/cdrom.png", *this->window, this->camara));
    SdlAnimation animacionCargando(texturaCargando);
    Area destAreaDeLaAnimacionCarga(250, 250, 400, 400);
    this->cargarTexturas(animacionCargando, destAreaDeLaAnimacionCarga);
    this->cargarTextos(animacionCargando, destAreaDeLaAnimacionCarga);
    this->cargarSonidos(animacionCargando, destAreaDeLaAnimacionCarga);
}

void SdlPartida::cargarTexturas(SdlAnimation &animacion, Area &dest) {
    std::string carpeta = "img";
    if (DIR * dpdf = opendir(carpeta.c_str())) {
        dirent *epdf = nullptr;
        std::string ruta;
        epdf = readdir(dpdf);
        while (epdf) {
            Tiempo tiempo(TIEMPO_CARGA_DATOS);
            animacion.animarCarga(dest);
            this->window->render();
            ruta = (std::string) epdf->d_name;
            if (ruta != "." && ruta != ".." && ruta != "Tag.txt") {
                std::string name = ruta;
                size_t posPunt = name.find(".");
                std::string nombre = name.substr(0, posPunt);
                this->texturas.insert(
                        std::make_pair(nombre,
                        (std::shared_ptr<SdlTexture>) new SdlTexture(
                        "img/" + ruta, *this->window, this->camara)));
            }
            epdf = readdir(dpdf);
        }
    }
}

void SdlPartida::cargarTextos(SdlAnimation &animacion, Area &dest) {
    for (int i = 0; i < MAX_VIDA_GUSANO; i++) {
        Tiempo tiempo(TIEMPO_CARGA_DATOS);
        animacion.animarCarga(dest);
        this->window->render();
        this->textos.insert(
                std::make_pair(std::to_string(i),
                (std::shared_ptr<SdlTexto>) new SdlTexto(
                std::to_string(i), "font/Roboto-Bold.ttf", 10, this->camara)));
    }
    this->textos.insert(std::make_pair("ganador",
            (std::shared_ptr<SdlTexto>) new SdlTexto(
            " FELICITACIONES SOS EL GANADOR!", "font/Roboto-Black.ttf",
            20, this->camara)));
    this->textos.insert(std::make_pair("perdedor",
            (std::shared_ptr<SdlTexto>) new SdlTexto(
            " PERDISTE EL JUEGO!!", "font/Roboto-Black.ttf", 20, this->camara)));
    this->textos.insert(std::make_pair("potencia",
            (std::shared_ptr<SdlTexto>) new SdlTexto(
            "Potencia: ", "font/Roboto-Black.ttf", 20, this->camara)));
    this->textos.insert(std::make_pair("viento",
            (std::shared_ptr<SdlTexto>) new SdlTexto(
            "Viento: ", "font/Roboto-Black.ttf", 20, this->camara)));
    this->textos.insert(std::make_pair("ms",
            (std::shared_ptr<SdlTexto>) new SdlTexto(
            "mts/seg", "font/Roboto-Black.ttf", 20, this->camara)));
    this->textos.insert(std::make_pair("punto",
            (std::shared_ptr<SdlTexto>) new SdlTexto(
            ".", "font/Roboto-Black.ttf", 20, this->camara)));
    this->textos.insert(std::make_pair("conteo",
            (std::shared_ptr<SdlTexto>) new SdlTexto(
            "Conteo: ", "font/Roboto-Black.ttf", 20, this->camara)));
    this->textos.insert(std::make_pair("jugador",
            (std::shared_ptr<SdlTexto>) new SdlTexto(
            "Turno del Jugador: ", "font/Roboto-Black.ttf", 20, this->camara)));
    this->textos.insert(std::make_pair("numeroJugador",
            (std::shared_ptr<SdlTexto>) new SdlTexto(
            "Jugador: ", "font/Roboto-Black.ttf", 20, this->camara)));    
}

void SdlPartida::cargarSonidos(SdlAnimation &animacion, Area &dest) {
    std::string carpeta = "sound";
    if (DIR * dpdf = opendir(carpeta.c_str())) {
        dirent *epdf = nullptr;
        std::string ruta;
        epdf = readdir(dpdf);
        while (epdf) {
            Tiempo tiempo(TIEMPO_CARGA_DATOS);
            animacion.animarCarga(dest);
            this->window->render();
            ruta = (std::string) epdf->d_name;
            if (ruta != "." && ruta != ".." && ruta != "Tag.txt") {
                std::string name = ruta;
                size_t posPunt = name.find(".");
                std::string nombre = name.substr(0, posPunt);
                std::string extension = name.substr(posPunt + 1);
                this->sonidos.insert(
                        std::make_pair(nombre,
                        (std::shared_ptr<SdlSonido>) new SdlSonido(
                        "sound/" + ruta, extension)));
            }
            epdf = readdir(dpdf);
        }
    }
}

void SdlPartida::mostrarError(const std::string &msg) {
    const SDL_MessageBoxButtonData buttons[]{
        {
            SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "ok"
        },
    };
    const SDL_MessageBoxColorScheme colorScheme = {
        { /* .colors (.r, .g, .b) */
            /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
            { 255, 0, 0},
            /* [SDL_MESSAGEBOX_COLOR_TEXT] */
            { 0, 255, 0},
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
            { 255, 255, 0},
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
            { 0, 0, 255},
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
            { 255, 0, 255}
        }
    };
    const SDL_MessageBoxData messageBoxData = {SDL_MESSAGEBOX_INFORMATION, /* .flags */
        NULL, /* .window */
        "Error", /* .title */
        msg.c_str(), /* message */
        SDL_arraysize(buttons), /* .numbuttons */
        buttons, /* .buttons */
        &colorScheme /* .colorScheme */};
    int buttonid;
    SDL_ShowMessageBox(&messageBoxData, &buttonid);
}

void SdlPartida::cargarArma(CargarArma cargaArma) {
    if (!this->gusanoEnTurno) {
        throw std::runtime_error("no existe el id del jugador");
    }
    int inclinacion = this->gusanoEnTurno->getInclinacion();
    std::string nombreSprite = "cargarArma" +
            std::to_string(cargaArma.getTipoArma()) +
            std::to_string(inclinacion);
    int armaActualCargada = this->gusanoEnTurno->handle(nombreSprite);
    if (!armaActualCargada) {
        auto search = this->texturas.find(nombreSprite);
        if (search != this->texturas.end()) {
            std::shared_ptr<State> estado(
                    new EstadoCargandoArma(this->texturas[nombreSprite]));
            this->gusanoEnTurno->setEstado(estado);
            this->gusanoEnTurno->setArma(cargaArma.getTipoArma());
            if(this->gusanoEnTurno->getArma()->tieneTiempo()){
                this->informacionDeCliente.habilitarTiempoDelArma();   
            }else{
                this->informacionDeCliente.deshabilitarTiempoDelArma();
            }
        }
    }
}

void SdlPartida::descargarArma() {
    std::string nombreSprite = "mirar"
            + std::to_string(this->gusanoEnTurno->getInclinacion());
    std::shared_ptr<State> estado(
            new EstadoAnimandoFijo(this->texturas[nombreSprite]));
    this->gusanoEnTurno->setEstado(estado);
    this->gusanoEnTurno->setArma(-1);
    this->informacionDeCliente.deshabilitarTiempoDelArma();
}

void SdlPartida::mover(MoverGusano movGusano) {
    SdlGusano *gusano = this->mapa->getGusano(movGusano.getIdGusano());
    if (!gusano) {
        throw std::runtime_error("no existe el id del gusano");
    }
    this->camara.seguirGusano(movGusano.getX(), movGusano.getY());
    std::string nombreSprite = movGusano.getEstadoToString() +
            std::to_string(movGusano.getInclinacion());
    int estadoAnteriorIgual = gusano->handle(nombreSprite);
    if (!estadoAnteriorIgual && movGusano.getEstadoGusano()) {
        auto search = this->texturas.find(nombreSprite);
        if (search != this->texturas.end()) {            
            std::shared_ptr<State> estado(
                    new EstadoMoviendo(this->texturas[nombreSprite]));
            gusano->setEstado(estado);
        } else {
            std::cout << "textura no encontrada " << nombreSprite << std::endl;
        }
    } else {
        gusano->mover(movGusano.getX(), movGusano.getY());
    }
}

void SdlPartida::moverPunteria(int direccionDeLaPunteria) {
    if (!this->gusanoEnTurno) {
        throw std::runtime_error("no existe el id del jugador");
    }
    int estadoValido = this->gusanoEnTurno->handle("punteria");
    if (estadoValido == 2) {
        std::string nombreSprite = "apuntar"
                + std::to_string(this->gusanoEnTurno->getArma()->getTipo())
                + std::to_string(this->gusanoEnTurno->getInclinacion());
        auto search = this->texturas.find(nombreSprite);
        if (search != this->texturas.end()) {
            std::shared_ptr<State> estado(
                    new EstadoApuntando(this->texturas[nombreSprite],
                    direccionDeLaPunteria));
            this->gusanoEnTurno->setEstado(estado);
        }
    }
    if (estadoValido == 1) {
        this->gusanoEnTurno->actualizarPunteria(direccionDeLaPunteria);
    }
}

void SdlPartida::atacar() {
    std::string nombreSprite = "atacar" +
            std::to_string(this->gusanoEnTurno->getArma()->getTipo()) +
            std::to_string(this->gusanoEnTurno->getDireccion());
    std::string nombreSonido = "atacar" +
            std::to_string(this->gusanoEnTurno->getArma()->getTipo());
    auto search = this->texturas.find(nombreSprite);
    if (search != this->texturas.end()) {
        std::shared_ptr<State> estado(
                new EstadoAtacando(this->texturas[nombreSprite],
                this->gusanoEnTurno->getAngulo()));
        this->gusanoEnTurno->setEstado(estado);
    }
    this->sonidos.at(nombreSonido)->play();
}

void SdlPartida::teletransportar(TeletransportarGusano teletransportar) {
    this->atacar();
    Area nuevaPosicion(teletransportar.getXVista(), teletransportar.getYVista(),
            TAM_GUSANO * MULTIPLICAR_VISTA,
            TAM_GUSANO * MULTIPLICAR_VISTA);
    this->gusanoEnTurno->setPosicion(nuevaPosicion);
}

void SdlPartida::actualizarVida(ActualizarVida actualizarVida) {
    SdlGusano *gusano = this->mapa->getGusano(actualizarVida.getIdGusano());
    if (!gusano) {
        throw std::runtime_error("no existe el id del gusano");
    }
    gusano->setVida(actualizarVida.getVida());
    if (!actualizarVida.getVida()) {
        std::string nombreSprite = "muriendo" +
                std::to_string(actualizarVida.getInclinacion());
        auto search = this->texturas.find(nombreSprite);
        if (search != this->texturas.end()) {
            std::shared_ptr<State> estado(
                    new EstadoMuriendo(this->texturas[nombreSprite]));
            gusano->setEstado(estado);
            this->sonidos.at("morir")->play();
        }
    } else {
        std::string nombreSprite = "herido" +
                std::to_string(actualizarVida.getInclinacion());
        auto search = this->texturas.find(nombreSprite);
        if (search != this->texturas.end()) {
            std::shared_ptr<State> estado(
                    new EstadoAnimandoFijo(this->texturas[nombreSprite]));
            gusano->setEstado(estado);
        }
    }
}

void SdlPartida::direccionar(int direccion) {
    this->gusanoEnTurno->setDireccion(direccion);
    this->camara.seguirGusano(this->gusanoEnTurno->getPosicion().getX(),
            this->gusanoEnTurno->getPosicion().getY());
}

void SdlPartida::mostrarGanador(NotificarGanador ganador) {
    if (this->cliente->getIdJugador() == ganador.getIdJugadorGanador()) {
        this->soyGanador = true;
    } else {
        this->soyGanador = false;
    }
    this->partidaFinalizada = true;
}

void SdlPartida::moverBala(MoverBala movBala) {
    this->mapa->moverProyectil(movBala);
    this->camara.seguirBala(movBala.getXVista(), movBala.getYVista());
}

void SdlPartida::impactarBala(ImpactarBala impacto) {        
    if (this->mapa->proyectilEsSanta(impacto.getIdBala())){
        this->sonidos.at("santa")->play();
    } else {
        this->sonidos.at("explosion")->play();
    }
    this->mapa->impactarProyectil(impacto);
}

void SdlPartida::destruirBala(DestruirBala destruir) {
    this->mapa->destruirProyectil(destruir.getIdBala());
    this->camara.desactivarSeguirBala();
}

void SdlPartida::mostrarMje(const std::string &mje) {
    const SDL_MessageBoxButtonData buttons[]{
        {
            SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "Aceptar"
        },
    };
    const SDL_MessageBoxColorScheme colorScheme = {
        { /* .colors (.r, .g, .b) */
            /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
            { 0, 125, 125},
            /* [SDL_MESSAGEBOX_COLOR_TEXT] */
            { 0, 255, 0},
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
            { 125, 255, 0},
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
            { 0, 0, 255},
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
            { 125, 0, 255}
        }
    };
    const SDL_MessageBoxData messageBoxData = {SDL_MESSAGEBOX_INFORMATION, /* .flags */
        NULL, /* .window */
        "Mensaje", /* .title */
        mje.c_str(), /* message */
        SDL_arraysize(buttons), /* .numbuttons */
        buttons, /* .buttons */
        &colorScheme /* .colorScheme */};
    int buttonid;
    SDL_ShowMessageBox(&messageBoxData, &buttonid);
}

void SdlPartida::finalizarPartida() {
    this->running = false;
}

void SdlPartida::notificarTiempoRestante(TiempoRestante tiempoRestante) {
    this->informacionDeCliente.actualizarTiempoRestante(
            tiempoRestante.getTiempoRestante());
}

void SdlPartida::informarViento(InformarViento viento) {
    this->informacionDeCliente.setViento(viento.getMagnitudVientoEnCentimetrosPorSegundo());
    std::string nombreSprite;
    nombreSprite = "viento" + std::to_string(viento.getDireccion());
    this->informacionDeCliente.setTexturaViento(this->texturas[nombreSprite]);
}

SdlPartida::~SdlPartida() {
}


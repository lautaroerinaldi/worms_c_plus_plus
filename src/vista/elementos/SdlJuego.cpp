#include <SDL2/SDL.h>
#include <iostream>
#include <exception>
#include <SDL2/SDL_image.h>
#include <unistd.h>
#include "SdlJuego.h"
#include "../estadosJuego/EstadoPantallaPrincipal.h"
#include "../estadosJuego/EstadoListandoJugadores.h"
#include "../estadosJuego/EstadoListandoPartidas.h"
#include "../estadosJuego/EstadoListandoEscenarios.h"

SdlJuego::SdlJuego(UsuarioAnonimo *anonimo) : anonimo(anonimo),running(true){
    this->window = SdlWindow::instance();
    if (!SdlWindow::inicializado()) {
        std::runtime_error("mal inicializada ventana");
    }
    this->cargarTexturasJuego();
    this->cargarTextosJuego();
    this->estado = new EstadoPantallaPrincipal(this);
    this->window->setTextura(this->texturas["fondo"]);
    this->window->fill();
    this->cantidadDeJugadores = 0;
    this->empezoPartida = false;
}

void SdlJuego::run() {
    try {
        this->anonimo->listarEscenarios();  
        SDL_Event event;

        while (this->running) {
            this->window->mostrarFondo();
            this->estado->render(this->texturas, this->textos);

            while (SDL_PollEvent(&event) != 0) {
                running = this->estado->Handle(event.type);
            }
            this->window->render();
            usleep(100000);
        }
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;        
    }
    if(!this->empezoPartida){
        this->window->release();
        this->anonimo->apagar();
    }    
}

void SdlJuego::mostrarMje(const std::string &mje) {
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

void SdlJuego::cargarTexturasJuego() {
    this->texturas.insert(std::make_pair("fondo", (std::shared_ptr<SdlTexture>)
            new SdlTexture("img/fondoWorms.jpeg", *this->window, this->camara)));
    this->texturas.insert(std::make_pair("header", (std::shared_ptr<SdlTexture>)
            new SdlTexture("img/header.jpg", *this->window, this->camara)));
    this->texturas.insert(std::make_pair("puntero", (std::shared_ptr<SdlTexture>)
            new SdlTexture("img/puntero.png", *this->window, this->camara)));
}

void SdlJuego::cargarTextosJuego() {
    this->textos.insert(std::make_pair("crear",
            (std::shared_ptr<SdlTexto>) new SdlTexto(
            "CREAR PARTIDA", "font/Roboto-Medium.ttf", 50, this->camara)));
    this->textos.insert(std::make_pair("unirse",
            (std::shared_ptr<SdlTexto>) new SdlTexto(
            "UNIRSE A PARTIDA", "font/Roboto-Medium.ttf", 50, this->camara)));
    this->textos.insert(std::make_pair("anio",
            (std::shared_ptr<SdlTexto>) new SdlTexto(
            " 2018 - TP TALLER -WORMS REMAKE", "font/Roboto-Black.ttf", 50, this->camara)));
    this->textos.insert(std::make_pair("creador1",
            (std::shared_ptr<SdlTexto>) new SdlTexto(
            " LEONARDO GALDAMES -", "font/Roboto-Black.ttf", 50, this->camara)));
    this->textos.insert(std::make_pair("creador2",
            (std::shared_ptr<SdlTexto>) new SdlTexto(
            " LAUTARO RINALDI -", "font/Roboto-Black.ttf", 50, this->camara)));
    this->textos.insert(std::make_pair("creador3",
            (std::shared_ptr<SdlTexto>) new SdlTexto(
            " FLORENCIA RUSCONI", "font/Roboto-Black.ttf", 50, this->camara)));
    this->textos.insert(std::make_pair("seleccionarJugadores",
            (std::shared_ptr<SdlTexto>) new SdlTexto(
            " SELECCIONE LA CANTIDAD DE JUGADORES", "font/Roboto-Black.ttf", 50, this->camara)));
    this->textos.insert(std::make_pair("2jugadores",
            (std::shared_ptr<SdlTexto>) new SdlTexto(
            " 2 JUGADORES", "font/Roboto-Medium.ttf", 50, this->camara)));
    this->textos.insert(std::make_pair("3jugadores",
            (std::shared_ptr<SdlTexto>) new SdlTexto(
            " 3 JUGADORES", "font/Roboto-Medium.ttf", 50, this->camara)));
    this->textos.insert(std::make_pair("4jugadores",
            (std::shared_ptr<SdlTexto>) new SdlTexto(
            " 4 JUGADORES", "font/Roboto-Medium.ttf", 50, this->camara)));
    this->textos.insert(std::make_pair("volver",
            (std::shared_ptr<SdlTexto>) new SdlTexto(
            " VOLVER AL MENU PRINCIPAL", "font/Roboto-Medium.ttf", 50, this->camara)));
    this->textos.insert(std::make_pair("seleccionarPartida",
            (std::shared_ptr<SdlTexto>) new SdlTexto(
            " SELECCIONE LA PARTIDA A UNIRSE", "font/Roboto-Black.ttf", 50, this->camara)));
    this->textos.insert(std::make_pair("seleccionarEscenario",
            (std::shared_ptr<SdlTexto>) new SdlTexto(
            " SELECCIONE EL ESCENARIO", "font/Roboto-Black.ttf", 50, this->camara)));
    this->textos.insert(std::make_pair("partida",
            (std::shared_ptr<SdlTexto>) new SdlTexto(
            " PARTIDA", "font/Roboto-Medium.ttf", 50, this->camara)));
    this->textos.insert(std::make_pair("escenario",
            (std::shared_ptr<SdlTexto>) new SdlTexto(
            " ESCENARIO", "font/Roboto-Medium.ttf", 50, this->camara)));
    this->textos.insert(std::make_pair("id",
            (std::shared_ptr<SdlTexto>) new SdlTexto(
            " ID", "font/Roboto-Medium.ttf", 50, this->camara)));
}

void SdlJuego::setEstado(int estado) {
    delete this->estado;
    switch (estado) {
        case LISTANDO_JUGADORES:            
            this->estado = new EstadoListandoJugadores(this);
            break;
        case PANTALLA_PRINCIPAL:
            this->estado = new EstadoPantallaPrincipal(this);
            break;
        case LISTANDO_PARTIDAS:            
            this->anonimo->listarPartidasNoIniciadas();
            usleep(100000);
            this->estado = new EstadoListandoPartidas(this, this->camara);
            break;
        case LISTANDO_ESCENARIOS:                        
            this->estado = new EstadoListandoEscenarios(this, this->camara);
            break;
    }
}

void SdlJuego::setCantidadDeJugadores(int cantidad) {
    this->cantidadDeJugadores = cantidad;
}


std::map<int, std::string> SdlJuego::getEscenarios() {
    return this->escenarios;
}

std::map<int, std::string> SdlJuego::getPartidas() {
    return this->partidas;
}

void SdlJuego::mostrarError(const std::string &msg) {
    const SDL_MessageBoxButtonData buttons[]{
        {
            SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "ok"
        },
    };
    const SDL_MessageBoxColorScheme colorScheme = {
        {{ 255, 0, 0},{ 0, 255, 0},{ 255, 255, 0},{ 0, 0, 255},{ 255, 0, 255}}
    };
    const SDL_MessageBoxData messageBoxData = {SDL_MESSAGEBOX_INFORMATION, /* .flags */
        NULL,"Error",msg.c_str(),SDL_arraysize(buttons),buttons,&colorScheme};
    int buttonid;
    SDL_ShowMessageBox(&messageBoxData, &buttonid);
}

void SdlJuego::setEscenarios(ListaEscenarios listaDeEscenarios) {
    std::cout<<listaDeEscenarios.getEscenarios().at(1)<<std::endl;
    this->escenarios = listaDeEscenarios.getEscenarios();
}

void SdlJuego::setPartidas(ListaPartidas listaDePartidas) {
    this->partidas = listaDePartidas.getPartidas();    
}

int SdlJuego::seleccionoEscenario(int idEscenario){
    CrearPartida crearPartida(idEscenario,this->cantidadDeJugadores);
    this->anonimo->crearYUnirseAPartida(crearPartida);
    return 0;
}

int SdlJuego::seleccionPartida(int idPartida){
    UnirseAPartida unirse(idPartida);
    this->anonimo->unirseAPartida(unirse);
    return 0;
}

void SdlJuego::notificarIdPartida(int id){
    std::string mje = "El id de la partida creada es "+ std::to_string(id);
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


void SdlJuego::cerrarPantallasIniciales(){
    this->running = false;
    this->empezoPartida = true;
}

SdlJuego::~SdlJuego() {
    delete this->estado;
}


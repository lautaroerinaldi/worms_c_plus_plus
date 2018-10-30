#include "SdlEventoTeclado.h"
#include <iostream>
#include "../../comun/Codigos.h"
#include "../componentes/SdlSonido.h"
#include <map>
#include "../../comun/Protocolo/Solicitudes/SolicitarArma.h"
#include "../../comun/Protocolo/Solicitudes/SolicitarAtacar.h"
#include "../../comun/Protocolo/Solicitudes/SolicitarMover.h"
#include "../../comun/Protocolo/Solicitudes/SolicitarRetroceso.h"
#include "../../comun/Protocolo/Solicitudes/SolicitarSaltar.h"
#include "../../comun/Protocolo/Visuales/DescargarArma.h"
#include "../../comun/Protocolo/Visuales/DireccionarGusano.h"
#include "../../comun/Protocolo/Visuales/MoverPunteria.h"

#define OK 1
#define ERROR 0

#define FRAMES_POTENCIA 16
#define CONTEO_ARMA_POR_DEFECTO 5

SdlEventoTeclado::SdlEventoTeclado(Destinatario *cliente) : cliente(cliente),
frame(0) {
}

void SdlEventoTeclado::procesarEvento(SDL_KeyboardEvent &keyEvent,
        SdlGusano *jugador,
        std::map<std::string, std::shared_ptr<SdlSonido>> &sonidos,
        SdlInformacion &informacion) {
    switch (keyEvent.keysym.sym) {
        case SDLK_LEFT:
            this->procesarIzquierda(jugador);
            break;
        case SDLK_RIGHT:
            this->procesarDerecha(jugador);
            break;
        case SDLK_UP:
            this->procesarPunteria(SUBIR_PUNTERIA, jugador);
            break;
        case SDLK_DOWN:
            this->procesarPunteria(BAJAR_PUNTERIA, jugador);
            break;
        case 8:
            this->procesarRetroceso(jugador, sonidos);
            break;
        case 13:
            this->procesarSalto(jugador, sonidos);
            break;
        case SDLK_0:
            this->procesarArma(BAZOOKA, jugador);
            break;
        case SDLK_1:
            this->procesarArma(BANANA, jugador);
            break;
        case SDLK_2:
            this->procesarArma(MORTERO, jugador);
            break;
        case SDLK_3:
            this->procesarArma(GRANADA_ROJA, jugador);
            break;
        case SDLK_4:
            this->procesarArma(GRANADA_VERDE, jugador);
            break;
        case SDLK_5:
            this->procesarArma(GRANADA_SANTA, jugador);
            break;
        case SDLK_6:
            this->procesarArma(DINAMITA, jugador);
            break;
        case SDLK_7:
            this->procesarArma(ATAQUE_AEREO, jugador);
            break;
        case SDLK_8:
            this->procesarArma(BATE_DE_BASEBALL, jugador);
            break;
        case SDLK_9:
            this->procesarArma(TELETRANSPORTACION, jugador);
            break;
        case SDLK_SPACE:
            this->procesarAcumuladorDePotencia(jugador, informacion);
            break;
        case SDLK_a:
            this->procesarAcumuladorDeTiempo(jugador, 1, informacion);
            break;
        case SDLK_s:
            this->procesarAcumuladorDeTiempo(jugador, 2, informacion);
            break;
        case SDLK_d:
            this->procesarAcumuladorDeTiempo(jugador, 3, informacion);
            break;
        case SDLK_f:
            this->procesarAcumuladorDeTiempo(jugador, 4, informacion);
            break;
        case SDLK_g:
            this->procesarAcumuladorDeTiempo(jugador, 5, informacion);
            break;
    }
}

void SdlEventoTeclado::procesarIzquierda(SdlGusano *jugador) {
    int solicitaCaminar = jugador->direccionar(IZQUIERDA);
    if (!solicitaCaminar) {
        SolicitarMover mover(IZQUIERDA);
        this->cliente->enviarMensaje(mover);
    } else {
        DireccionarGusano direccionar(IZQUIERDA);
        this->cliente->enviarMensaje(direccionar);
    }
}

void SdlEventoTeclado::procesarDerecha(SdlGusano *jugador) {
    int solicitaCaminar = jugador->direccionar(DERECHA);
    if (!solicitaCaminar) {
        SolicitarMover mover(DERECHA);
        this->cliente->enviarMensaje(mover);
    } else {
        DireccionarGusano direccionar(DERECHA);
        this->cliente->enviarMensaje(direccionar);
    }
}

void SdlEventoTeclado::procesarArma(int arma, SdlGusano *jugador) {
    if (arma == jugador->getArma()->getTipo()) {
        DescargarArma descarga;
        this->cliente->enviarMensaje(descarga);
    } else {
        SolicitarArma armaSolicitar(arma);
        this->cliente->enviarMensaje(armaSolicitar);
    }
}

void SdlEventoTeclado::procesarPunteria(int direccion, SdlGusano *jugador) {
    MoverPunteria movPunteria(direccion);
    this->cliente->enviarMensaje(movPunteria);
}

void SdlEventoTeclado::procesarSalto(SdlGusano *jugador, std::map<std::string, std::shared_ptr<SdlSonido>> &sonidos) {
    sonidos.at("saltar")->play();
    SolicitarSaltar saltar(jugador->getDireccion());
    this->cliente->enviarMensaje(saltar);
}

void SdlEventoTeclado::procesarRetroceso(SdlGusano *jugador, std::map<std::string, std::shared_ptr<SdlSonido>> &sonidos) {
    sonidos.at("retroceso")->play();
    SolicitarRetroceso retroceso(jugador->getDireccion());
    this->cliente->enviarMensaje(retroceso);
}

void SdlEventoTeclado::procesarAtaque(SdlPartida *partida, SdlGusano *jugador,
        SdlInformacion &informacion) {
    int puedeAtacar = jugador->puedeAtacar();
    if (puedeAtacar) {
        if ((jugador->getArma()->getTipo() == ATAQUE_AEREO) ||
                (jugador->getArma()->getTipo() == TELETRANSPORTACION)) {
            partida->mostrarError("debe tocar el boton del mouse y apuntar para disparar esta arma");
        } else {
            int angulo = jugador->getAngulo();
            SolicitarAtacar soliAtacar(angulo, jugador->getDireccion(),
                    jugador->getArma()->getPotencia(),
                    jugador->getArma()->getConteo(), -1, -1);
            cliente->enviarMensaje(soliAtacar);
            informacion.mostrarValorPotencia(0);
            informacion.deshabilitarPotencia();    
            if(jugador->getArma()->getTipo() != BATE_DE_BASEBALL){
                DescargarArma descarga;
                this->cliente->enviarMensaje(descarga);    
            }
        }        
    }
}

void SdlEventoTeclado::procesarSoltado(SDL_KeyboardEvent& keyEvent,
        SdlPartida* partida, SdlGusano *jugador, SdlInformacion &informacion) {
    if (keyEvent.keysym.sym == SDLK_SPACE) {
        this->procesarAtaque(partida, jugador, informacion);
        informacion.deshabilitarTiempoDelArma();
        jugador->getArma()->setConteo(CONTEO_ARMA_POR_DEFECTO);
    }
}

void SdlEventoTeclado::procesarAcumuladorDePotencia(SdlGusano* jugador,
        SdlInformacion &informacion) {    
    if(jugador->getArma()->tienePotencia()){
        informacion.habilitarPotencia();        
        if (this->frame == FRAMES_POTENCIA){
            jugador->getArma()->acumularPotencia();
            this->frame = 0;
        }
        informacion.mostrarValorPotencia(jugador->getArma()->getPotencia());
        this->frame++;
    }
}

void SdlEventoTeclado::procesarAcumuladorDeTiempo(SdlGusano* jugador,
        int tiempo, SdlInformacion &informacion) {
    jugador->getArma()->setConteo(tiempo);
    informacion.setTiempoDelArma(tiempo);
}

SdlEventoTeclado::~SdlEventoTeclado() {
}


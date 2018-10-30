#ifndef SDLEVENTOTECLADO_H
#define SDLEVENTOTECLADO_H

#include <SDL2/SDL_events.h>
#include "../elementos/SdlPartida.h"
#include "../elementos/SdlGusano.h"
#include "../../cliente/Cliente.h"
#include "../componentes/SdlSonido.h"
#include "../elementos/SdlInformacion.h"

#include <map>

class Destinatario;

class SdlEventoTeclado {
private:
    Destinatario *cliente;
    int frame;
    
public:
    //constructor del evento Teclado    
    SdlEventoTeclado(Destinatario *cliente);

    //procesa el evento pasado por parametro    
    void procesarEvento(SDL_KeyboardEvent &keyEvent,
            SdlGusano *jugador,std::map<std::string, 
            std::shared_ptr<SdlSonido>> &sonidos,SdlInformacion &informacion);

    //realiza la logica del boton derecha
    void procesarDerecha( SdlGusano *jugador);

    //realiza la logica del boton izquierda
    void procesarIzquierda( SdlGusano *jugador);

    //procesa las armas pasadas por parametro    
    void procesarArma(int arma, SdlGusano *jugador);

    //procesa el salto
    void procesarSalto(SdlGusano *jugador,std::map<std::string, 
                                        std::shared_ptr<SdlSonido>> &sonidos);
    
    //procesa la vuelta atras
    void procesarRetroceso(SdlGusano *jugador,
                    std::map<std::string, std::shared_ptr<SdlSonido>> &sonidos);

    //procesa el ataque
    void procesarAtaque(SdlPartida *partida, SdlGusano *jugador,
                                                   SdlInformacion &informacion);
    
    //procesa la punteria
    void procesarPunteria(int direccion,SdlGusano *jugador);
    
    //procesa el boton apretado
    void procesarSoltado(SDL_KeyboardEvent &keyEvent, SdlPartida *partida,
                                SdlGusano *jugador,SdlInformacion &informacion);
    
    //procesa y acumula potencia
    void procesarAcumuladorDePotencia(SdlGusano *jugador, 
                                                   SdlInformacion &informacion);
    
    //acumula o resta el tiempo del arma
    void procesarAcumuladorDeTiempo(SdlGusano *jugador,int tiempo, 
                                                   SdlInformacion &informacion);
    
    //destructor del evento Teclado    
    ~SdlEventoTeclado();
};

#endif /* SDLEVENTOTECLADO_H */


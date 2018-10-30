#ifndef SDLJUEGO_H
#define SDLJUEGO_H

#include <map>
#include <string>
#include <memory>

#include "../componentes/SdlWindow.h"
#include "../componentes/SdlTexture.h"
#include "../componentes/Area.h"
#include "../componentes/SdlTexto.h"
#include "../estadosJuego/EstadoJuego.h"
#include "../CodigosVista.h"
#include "../elementos/SdlCamara.h"
#include "../../comun/UsuarioAnonimo.h"
#include "../../comun/Protocolo/Listas/ListaEscenarios.h"
#include "../../comun/Protocolo/Listas/ListaPartidas.h"
#include "../../comun/Threads/Thread.h"

class SdlJuego : public Thread{
private:
    UsuarioAnonimo *anonimo;
    bool running;
    SdlWindow *window;
    EstadoJuego *estado;
    typedef std::map<std::string, std::shared_ptr<SdlTexture>> Texturas;
    Texturas texturas;
    std::map<std::string, std::shared_ptr<SdlTexto>> textos;
    int cantidadDeJugadores;
    std::map<int, std::string> partidas;
    std::map<int, std::string> escenarios;
    SdlCamara camara;
    bool empezoPartida;
    //    Cliente *cliente;

public:
    //constructor del juego
    SdlJuego(UsuarioAnonimo *anonimo);

    //corre la logica de la pantalla principal del juego
    void run();

    //carga las texturas de la pantalla principal
    void cargarTexturasJuego();

    //carga los textos de la pantalla principal
    void cargarTextosJuego();

    //carga las areas de la pantalla principal
    void cargarAreasJuego();

    //setea el estado del juego
    void setEstado(int estado);

    //setea la cantidad de jugadores
    void setCantidadDeJugadores(int cantidad);

    
    //devuelve las partidas
    std::map<int, std::string> getPartidas();

    //devuelve los escenarios
    std::map<int, std::string> getEscenarios();

    
    //devuelve las partidas
    void setPartidas(ListaPartidas listaDePartidas);

    //devuelve los escenarios
    void setEscenarios(ListaEscenarios listaDeEscenarios);

    //escenario seleccionado para crearlo
    int seleccionoEscenario(int idEscenario);
    
    //partida seleccionada para unirse
    int seleccionPartida(int idPartida);
        
    //notifica al cliente el id de la partida
    void notificarIdPartida(int id);
    
    //muestra el mensaje pasado por parametro
    void mostrarMje(const std::string &mensaje);
    
    //muestra un error
    void mostrarError(const std::string &error);
    
    //cierra las pantallas iniciales
    void cerrarPantallasIniciales();
    
    //llama al destructor del juego y libera sus recursos
    virtual ~SdlJuego();

};

#endif /* SDLJUEGO_H */


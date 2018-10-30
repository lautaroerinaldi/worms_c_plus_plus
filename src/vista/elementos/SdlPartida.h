#ifndef SDLPARTIDA_H
#define SDLPARTIDA_H

#include <memory>
#include <map>
#include "SdlMapa.h"
#include "../componentes/SdlWindow.h"
#include "../componentes/SdlAnimation.h"
#include "../componentes/SdlTexto.h"
#include "../componentes/SdlSonido.h"
#include "../estadosGusanos/State.h"
#include "../../comun/Protocolo/ActualizarVida.h"
#include "../../comun/Protocolo/Armas/CargarArma.h"
#include "../../comun/Protocolo/Armas/TeletransportarGusano.h"
#include "../../comun/Protocolo/Balas/CrearBala.h"
#include "../../comun/Protocolo/Balas/DestruirBala.h"
#include "../../comun/Protocolo/Escenario/CrearGusano.h"
#include "../../comun/Protocolo/Escenario/CrearViga.h"
#include "../../comun/Protocolo/Balas/MoverBala.h"
#include "../../comun/Protocolo/Balas/ImpactarBala.h"
#include "../../comun/Protocolo/MovimientosGusanos/MoverGusano.h"
#include "../../comun/Protocolo/NotificarGanador.h"
#include "../../comun/Protocolo/Turnos/FinalizarTurno.h"
#include "../../comun/Protocolo/Turnos/IniciarTurno.h"
#include "../../comun/Protocolo/Turnos/TiempoRestante.h"
#include "../../comun/Protocolo/InformarViento.h"
#include "../elementos/SdlCamara.h"
#include "../../comun/Threads/Thread.h"
#include "SdlInformacion.h"


class Destinatario;

/**
 * Hereda de Thread. Lanza un nuevo hilo.
 */
class SdlPartida : public Thread {
private:
    Destinatario * cliente;
    bool running;
    SdlWindow *window;
    SdlMapa *mapa;
    SdlInformacion informacionDeCliente;
    typedef std::map<std::string, std::shared_ptr<SdlTexture>> TexturasArray;
    TexturasArray texturas;
    std::map<std::string, std::shared_ptr<SdlSonido>> sonidos;
    std::map<std::string, std::shared_ptr<SdlTexto>> textos;    
    SdlGusano *gusanoEnTurno;
    int jugador;
    bool partidaFinalizada;
    bool soyGanador;
    SdlCamara camara;

protected:
    //corre la vista de la partida
    /**
     * Lanza el ciclo en un nuevo hilo, porque tiene un while que bloquea al while del cliente.
     * Se invoca llamando al método START()
     */
    void run();

public:
    //constructor de la partida
    SdlPartida(Destinatario * cliente);

    //inicializa la partida
    void init();

    //carga todos los componentes necesarios a los map
    //texturas, texto y sonidos
    void cargarTodo();

    //cargar texturas
    void cargarTexturas(SdlAnimation &animacion, Area &dest);

    //carga textos
    void cargarTextos(SdlAnimation &animacion, Area &dest);

    //carga los sonidos
    void cargarSonidos(SdlAnimation &animacion, Area &dest);

    //crea una viga y lo guarda en el mapa
    int crearViga(CrearViga crearViga);

    //crea un gusano y lo guarda en el mapa
    int crearGusano(CrearGusano gusano);

    //crea el fondo y lo guarda en el mapa
    int crearFondo();

    //muestra un error en la pantalla
    void mostrarError(const std::string &mje);

    //carga las armas
    void cargarArma(CargarArma cargaArma);

    //descarga el arma y cambia el estado a lazy
    void descargarArma();

    //mueve el gusano
    void mover(MoverGusano movGusano);

    //mueve la punteria la punteria
    void moverPunteria(int direccionDeLaPunteria);

    //el gusano efectua un ataque
    void atacar();

    //actualiza la vida de los gusanos
    void actualizarVida(ActualizarVida actualizarVida);

    //inicializar turno
    void iniciarTurno(IniciarTurno turno);

    //finalizar turno
    void finalizarTurno(FinalizarTurno finTurno);

    //direccionar la posicion del gusano
    void direccionar(int direccion);

    //muestra por pantalla el jugador ganador
    void mostrarGanador(NotificarGanador ganador);

    //muestra un mensaje por pantalla
    void mostrarMje(const std::string &mje);

    //teletransporta el gusano a la posicion indicada
    void teletransportar(TeletransportarGusano teletransportar);

    //crea una bala
    void crearBala(CrearBala bala);

    //mover una bala
    void moverBala(MoverBala movBala);

    //impacto de la bala
    void impactarBala(ImpactarBala impacto);

    //destruye la bala
    void destruirBala(DestruirBala destruir);

    //cierra la ventana
    void finalizarPartida();

    //recibe el tiempo restante para mostrarlo por pantalla
    void notificarTiempoRestante(TiempoRestante tiempoRestante);
    
    //muestra el viento por pantalla
    void informarViento(InformarViento viento);
    
    //destructor de la partida
    ~SdlPartida();
};

#endif /* SDLPARTIDA_H */


#ifndef SDLINFORMACION_H
#define SDLINFORMACION_H

#include <map>
#include <memory>

#include "../componentes/Area.h"
#include "../componentes/SdlTexto.h"
#include "../componentes/SdlTexture.h"

class SdlInformacion {
private:
    Area srcBorde;
    Area srcArea;
    int tiempoRestante;
    int potencia;
    bool mostrarPotencia;
    int viento;
    bool mostrarViento;
    int tiempoArma;
    bool mostrarTiempoArma;
    int turnoJugador;
    int numeroJugador;
    std::shared_ptr<SdlTexture> texturaViento;
    

public:
    //constructor de la informacion a usuario
    SdlInformacion();

    //actualiza el tiempo
    void actualizarTiempoRestante(int tiempo);

    //renderiza la informacion
    void render(std::map<std::string, std::shared_ptr<SdlTexto>> &textos);

    //habilita para mostrar la potencia
    void habilitarPotencia();

    //deshabilita para mostrar la potencia
    void deshabilitarPotencia();

    //actualiza el valor de la potencia
    void mostrarValorPotencia(int potencia);

    //setea el valor del viento
    void setViento(int viento);

    //setea la textura del viento
    void setTexturaViento(std::shared_ptr<SdlTexture> &texturaViento);

    //renderiza el viento
    void dibujarViento(std::map<std::string,
                                     std::shared_ptr<SdlTexto>> &textos);

    //habilita para mostrar el tiempo del arma
    void habilitarTiempoDelArma();

    //deshabilita para mostrar el tiempo del arma
    void deshabilitarTiempoDelArma();

    //actualiza el valor del tiempo del arma
    void setTiempoDelArma(int tiempo);
    
    //actualiza el turno del jugador
    void actualizarTurno(int jugador);

    //setea el numero del jugador
    void setNumeroJugador(int numeroJugador);
    
    //destructor de la informacion a usuario
    virtual ~SdlInformacion();

};

#endif /* SDLINFORMACION_H */


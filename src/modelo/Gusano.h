#ifndef WORMS_SRC_MODEL_GUSANO_H_
#define WORMS_SRC_MODEL_GUSANO_H_

#include "../Box2D/Box2D.h"
#include "../modelo/CuerpoMundo.h"

#include <string>

class Gusano : public CuerpoMundo {
	int id;
    int id_jugador;
    b2Vec2 posicion;
    float altura_incio_caida;
    b2Body* cuerpo;
    int vida;
    b2Vec2 velocidadCaminata;
    b2Vec2 velocidadSalto;
    b2Vec2 velocidadSaltoAtras;
    int inclinacion;
    int estado;
    bool activo;
    int enContactoConSuelo;
    bool cambioDeEstado;
    bool sufrio_danio;
    float angulo_viga;
public:
    //Constructor
    Gusano(const int id, const int jugador, const float x, const float y,
    		const int inclinacion, const int vida);
    //Destructor
    virtual ~Gusano();
    //Getter id
    int obtenerID();
    //Getter id de jugador
    int obtenerIDJugador();
    //Getter vida
    int obtenerVida();
    //Getter inclinacion
    int obtenerInclinacion();
    //Getter estado
    int obtenerEstado();
    //Verificar si hubo cambio de estado. Solo puede llamarse una vez.
    //(marca que no hubo cambios)
    bool cambioEstado();
    //Verifica si hay cambio la posicion (Utilizar siempre antes de obtener)
    bool cambioPosicion();
    //Getter de posicion (cambia referencia a posicion anterior)
    b2Vec2 obtenerPosicion();
    //Setter cuerpo box2d
    void agregarCuerpo(b2Body* cuerpoGus);
    //Getter de cuerpo de mundo
    b2Body* obtenerCuerpo();
    //Agrega puntos de vida
    void sumarVida(int puntos);
    //Genera daño (quita puntos de vida)
    void restarVida(int puntos);
    //Proboca la muerte del gusano
    void morir();
    //Verificar si sufrio daño Solo puede llamarse una vez.
    //(marca como no dañado)
    bool estaHerido();
    //Designar como gusano activo
    void activar();
    //Quitar designacion de gusano activo
    void desactivar();
    //Comprobar si el gusano es el activo
    bool estaActivo();
    //Hace que el gusano deje de moverse
    void frenar();
    //Hace que el gusano se quede quieto
    void detener();
    //Hace que el gusano camine en la direccion indicada
    bool caminar(const int direccion);
    //Hace que el gusano salte en la direccion indicada
    bool saltar(const int direccion);
    //Hace que el gusano salte hacia atras
    bool retroceder(const int direccion);
    //Marca el contacto con el suelo
    void aterrizar(float angulo_viga);
    //Desmarca el contacto con el suelo
    void despegar();
    //Marca choque con los bordes del escenario:
    void choco();
    //Teletransportar
    void teletransportar(b2Vec2 posicion);
    //Agrega impulso de vuelo por impacto de explosion
    void recibirImpulso(const b2Vec2 impulso, const b2Vec2 punto_impacto);
};

#endif /* WORMS_SRC_MODEL_GUSANO_H_ */

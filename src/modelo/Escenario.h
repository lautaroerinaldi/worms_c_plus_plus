#ifndef WORMS_SRC_MODEL_ESCENARIO_H_
#define WORMS_SRC_MODEL_ESCENARIO_H_

#include <list>

#include "Box2D/Box2D.h"
#include "modelo/CuerpoMundo.h"
#include "modelo/Gusano.h"
#include "modelo/Viga.h"
#include "CodigosModelo.h"
#include "extensionBox2D/ObservadorContactos.h"
#include "modelo/Bala.h"

class Escenario {
    float dim_x;
    float dim_y;
    b2World mundo;
    CuerpoMundo agua;
    CuerpoMundo borde;
    ObservadorContactos observador_contactos;
    float viento;
public:
    //Constructor
    Escenario();
    //Constructor
    ~Escenario();
    //Agrega una viga en el escenario
    void insertarViga(Viga& viga);
    //Agrega una gusano en el escenario
    void insertarGusano(Gusano& gusano);
    //Agregar una bala en el escenario
    void agregarBala(Bala& bala, bool viento, bool rebote);
    //Paso de simulacion de mundo
    void simularMundo();
    //Paso de tiempo 0 para uso de explosiones
    void simularMundoCero();
    //Remueve un gusano del mundo
    void removerGusano(Gusano& gusano);
    //Remueve una bala del mundo
    void removerBala(Bala& bala);
    //Verifica si puede moverse el gusano a una posicion
    bool posicionLibre(b2Vec2 posicion);
    //Busca gusanos cercanos al gusano pasado en la direccion indicada
    void obtenerGusanosCercanos(Gusano& gusano, const int direccion,
    		std::list<Gusano*>& gusanos_cercanos);
    //Obtiene el viento
    float obtenerViento();
private:
    //Arma los bordes del escenario
    void armarBordes();
};

#endif /* WORMS_SRC_MODEL_ESCENARIO_H_ */

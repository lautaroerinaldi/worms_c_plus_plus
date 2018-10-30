#ifndef WORMS_SRC_MODEL_VIGA_H_
#define WORMS_SRC_MODEL_VIGA_H_

#include "../Box2D/Box2D.h"
#include "../modelo/CuerpoMundo.h"

#include <string>

class Viga : public CuerpoMundo {
	float longitud;
    float angulo;
    b2Vec2 posicion_inicial;
public:
    //Constructor
    Viga(const float lon, const float angulo, const float x, const float y);
    //Destructor
    virtual ~Viga();
    //Getter longitud
    float obtenerLongitud();
    //Getter angulo
    float obtenerAngulo();
    //Getter posicion de inicio de viga
    b2Vec2 obtenerPosicionInicial();
};

#endif /* WORMS_SRC_MODEL_VIGA_H_ */

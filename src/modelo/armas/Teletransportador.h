#ifndef WORMS_SRC_MODELO_ARMAS_TELETRANSPORTADOR_H_
#define WORMS_SRC_MODELO_ARMAS_TELETRANSPORTADOR_H_

#include "modelo/armas/ArmaGenerica.h"
#include "modelo/Escenario.h"
#include "modelo/Gusano.h"

#include "Box2D/Box2D.h"

class Teletransportador: public ArmaGenerica {
public:
	//Constructor
	Teletransportador();
	//Destructor
	virtual ~Teletransportador();
	//Produce el disparo (teletransporta)
	bool disparar(Escenario& escenario, Gusano& gusano, b2Vec2 posicion);
};

#endif /* WORMS_SRC_MODELO_ARMAS_TELETRANSPORTADOR_H_ */

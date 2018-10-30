#ifndef WORMS_SRC_MODELO_ARMAS_BATEDEBASEBALL_H_
#define WORMS_SRC_MODELO_ARMAS_BATEDEBASEBALL_H_

#include "ArmaGenerica.h"
#include "modelo/Escenario.h"
#include "modelo/Gusano.h"

#include "Box2D/Box2D.h"

class BateDeBaseball: public ArmaGenerica {
public:
	//Constructor
	BateDeBaseball();
	//Destructor
	virtual ~BateDeBaseball();
	//Ejecuta un disparo: Realiza un bateo
	void disparar(Escenario& escenario, Gusano& gusano, const int direccion,
			float angulo);
};

#endif /* WORMS_SRC_MODELO_ARMAS_BATEDEBASEBALL_H_ */

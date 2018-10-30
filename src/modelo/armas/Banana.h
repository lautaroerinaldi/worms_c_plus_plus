#ifndef WORMS_SRC_MODELO_ARMAS_BANANA_H_
#define WORMS_SRC_MODELO_ARMAS_BANANA_H_

#include "ArmaGenerica.h"
#include "modelo/Escenario.h"
#include "modelo/Bala.h"

class Banana: public ArmaGenerica {
public:
	//Constructor
	Banana();
	//Destructor
	virtual ~Banana();
	//Realiza el disparo de la granada
	void disparar(Bala& bala, Escenario& escenario, const int potencia);
};

#endif /* WORMS_SRC_MODELO_ARMAS_BANANA_H_ */

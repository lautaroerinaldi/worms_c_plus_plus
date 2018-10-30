#ifndef WORMS_SRC_MODELO_ARMAS_MORTERO_H_
#define WORMS_SRC_MODELO_ARMAS_MORTERO_H_

#include "ArmaGenerica.h"
#include "modelo/Bala.h"
#include "modelo/Escenario.h"

class Mortero: public ArmaGenerica {
public:
	//Constructor
	Mortero();
	//Destructor
	virtual ~Mortero();
	//Realiza el disparo de la bala
	void disparar(Bala& bala, Escenario& escenario, const int potencia);
};

#endif /* WORMS_SRC_MODELO_ARMAS_MORTERO_H_ */

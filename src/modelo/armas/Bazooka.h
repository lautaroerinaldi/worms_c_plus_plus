#ifndef WORMS_SRC_MODELO_ARMAS_BAZOOKA_H_
#define WORMS_SRC_MODELO_ARMAS_BAZOOKA_H_

#include "ArmaGenerica.h"
#include "modelo/Bala.h"
#include "modelo/Escenario.h"

class Bazooka: public ArmaGenerica {
public:
	//Constructor
	Bazooka();
	//Destructor
	virtual ~Bazooka();
	//Dispara bala
	void disparar(Bala& bala, Escenario& escenario, const int potencia);
};

#endif /* WORMS_SRC_MODELO_ARMAS_BAZOOKA_H_ */

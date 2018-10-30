#ifndef WORMS_SRC_MODELO_ARMAS_DINAMITA_H_
#define WORMS_SRC_MODELO_ARMAS_DINAMITA_H_

#include "ArmaGenerica.h"
#include "modelo/Bala.h"
#include "modelo/Escenario.h"

class Dinamita: public ArmaGenerica {
public:
	//Constructor
	Dinamita();
	//Destructor
	virtual ~Dinamita();
	//Dispara la bala
	void disparar(Bala& bala, Escenario& escenario);
};

#endif /* WORMS_SRC_MODELO_ARMAS_DINAMITA_H_ */

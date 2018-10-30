#ifndef WORMS_SRC_MODELO_ARMAS_GRANADASANTA_H_
#define WORMS_SRC_MODELO_ARMAS_GRANADASANTA_H_

#include "ArmaGenerica.h"
#include "modelo/Escenario.h"
#include "modelo/Bala.h"

class GranadaSanta: public ArmaGenerica {
public:
	//Constructor
	GranadaSanta();
	//Destructor
	virtual ~GranadaSanta();
	//Realiza el disparo de la granada
	void disparar(Bala& bala, Escenario& escenario, const int potencia);
};

#endif /* WORMS_SRC_MODELO_ARMAS_GRANADASANTA_H_ */

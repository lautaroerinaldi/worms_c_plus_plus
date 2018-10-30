#ifndef WORMS_SRC_MODELO_ARMAS_GRANADAROJA_H_
#define WORMS_SRC_MODELO_ARMAS_GRANADAROJA_H_

#include "ArmaGenerica.h"
#include "modelo/Escenario.h"
#include "modelo/Bala.h"

class GranadaRoja: public ArmaGenerica {
public:
	//Constructor
	GranadaRoja();
	//Destructor
	virtual ~GranadaRoja();
	//Realiza el disparo de la granada
	void disparar(Bala& bala, Escenario& escenario, const int potencia);
};

#endif /* WORMS_SRC_MODELO_ARMAS_GRANADAROJA_H_ */

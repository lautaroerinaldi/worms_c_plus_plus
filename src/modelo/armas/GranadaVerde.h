#ifndef WORMS_SRC_MODELO_ARMAS_GRANADAVERDE_H_
#define WORMS_SRC_MODELO_ARMAS_GRANADAVERDE_H_

#include "ArmaGenerica.h"
#include "modelo/Escenario.h"
#include "modelo/Bala.h"

class GranadaVerde: public ArmaGenerica {
public:
	//Constructor
	GranadaVerde();
	//Destructor
	virtual ~GranadaVerde();
	//Realiza el disparo de la granada
	void disparar(Bala& bala, Escenario& escenario, const int potencia);
};

#endif /* WORMS_SRC_MODELO_ARMAS_GRANADAVERDE_H_ */

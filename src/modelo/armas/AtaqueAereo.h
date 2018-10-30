#ifndef WORMS_SRC_MODELO_ARMAS_ATAQUEAEREO_H_
#define WORMS_SRC_MODELO_ARMAS_ATAQUEAEREO_H_

#include "ArmaGenerica.h"
#include "modelo/Bala.h"
#include "modelo/Escenario.h"

#include <vector>

class AtaqueAereo: public ArmaGenerica {
public:
	//Constructor
	AtaqueAereo();
	//Destructor
	virtual ~AtaqueAereo();
	//Realiza el disparo: Lanza 6 misiles
	void disparar(Escenario& escenario, std::vector<Bala*> misiles);
};

#endif /* WORMS_SRC_MODELO_ARMAS_ATAQUEAEREO_H_ */

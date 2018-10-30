#ifndef WORMS_SRC_MODELO_ARMAGENERICA_H_
#define WORMS_SRC_MODELO_ARMAGENERICA_H_

#include "../../comun/Codigos.h"

class ArmaGenerica {
protected:
	bool municiones_infinitas;
	int municiones;
	int danio;
	int radio;
public:
	//Constructor
	ArmaGenerica();
	//Destructor
	virtual ~ArmaGenerica();
	//Verifica si se puede utilizar (municiones disponibles)
	virtual bool tieneMuniciones();
	//Permite configurar las municiones del arma
	virtual void cambiarMuniciones(const int municiones);
};

#endif /* WORMS_SRC_MODELO_ARMAGENERICA_H_ */

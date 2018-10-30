#ifndef WORMS_SRC_MODELO_EXTENSIONBOX2D_VERIFICADORAREAMUNDO_H_
#define WORMS_SRC_MODELO_EXTENSIONBOX2D_VERIFICADORAREAMUNDO_H_

#include "Box2D/Box2D.h"

#include <vector>

class VerificadorAreaMundo: public b2QueryCallback {
	std::vector<b2Body*> cuerposEncontrados;
public:
	//Constructor
	VerificadorAreaMundo();
	//Destructor
	virtual ~VerificadorAreaMundo();
	//Verificador de fixtures
	bool ReportFixture(b2Fixture* fixture) override;
	//Obtener cuerpos encontrados
	std::vector<b2Body*>& obtenerCuerpos();
};

#endif /* WORMS_SRC_MODELO_EXTENSIONBOX2D_VERIFICADORAREAMUNDO_H_ */

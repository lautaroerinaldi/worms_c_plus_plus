#ifndef WORMS_SRC_MODELO_EXTENSIONBOX2D_VERIFICADORRAYO_H_
#define WORMS_SRC_MODELO_EXTENSIONBOX2D_VERIFICADORRAYO_H_

#include "Box2D/Box2D.h"
#include <list>
#include "modelo/Gusano.h"

class VerificadorRayo: public b2RayCastCallback {
	std::list<Gusano*>& gusanos;
public:
	//Constructor
	VerificadorRayo(std::list<Gusano*>& gusanos);
	//Destructor
	virtual ~VerificadorRayo();
	//Metodo a utilizar
	float32 ReportFixture(b2Fixture* fixture, const b2Vec2&, const b2Vec2&,
			float32) override;
};

#endif /* WORMS_SRC_MODELO_EXTENSIONBOX2D_VERIFICADORRAYO_H_ */

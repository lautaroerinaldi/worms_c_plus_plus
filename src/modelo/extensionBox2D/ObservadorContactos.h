#ifndef WORMS_SRC_MODELO_EXTENSIONBOX2D_OBSERVADORCONTACTOS_H_
#define WORMS_SRC_MODELO_EXTENSIONBOX2D_OBSERVADORCONTACTOS_H_

#include "Box2D/Box2D.h"

#include "../modelo/Gusano.h"
#include "../modelo/Viga.h"

class ObservadorContactos: public b2ContactListener {
public:
	//Constructor
	ObservadorContactos();
	//Destructor
	virtual ~ObservadorContactos();
	//Inicio de contacto
	void BeginContact(b2Contact* contact) override;
	//Fin de contacto
	void EndContact(b2Contact* contact) override;
	//Momento de inicio de solucion de contacto
	void PreSolve(b2Contact* contact, const b2Manifold*) override;
	//Momento de fin de solucion de contacto
	void PostSolve(b2Contact* contact, const b2ContactImpulse*)override;
};

#endif /* WORMS_SRC_MODELO_EXTENSIONBOX2D_OBSERVADORCONTACTOS_H_ */

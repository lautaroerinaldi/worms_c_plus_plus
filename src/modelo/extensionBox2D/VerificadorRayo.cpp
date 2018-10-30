#include "VerificadorRayo.h"

#include "modelo/CuerpoMundo.h"
#include "modelo/CodigosModelo.h"

VerificadorRayo::VerificadorRayo(std::list<Gusano*>& gusanos) : gusanos(gusanos) {
}

VerificadorRayo::~VerificadorRayo() {
}

float32 VerificadorRayo::ReportFixture(b2Fixture* fixture, const b2Vec2&,
		const b2Vec2&,	float32) {
	CuerpoMundo* cuerpo = (CuerpoMundo*) fixture->GetBody()->GetUserData();
	if (cuerpo->obtenerTipo() == GUSANO){
		this->gusanos.push_back((Gusano*)cuerpo);
	}
	return 1;
}

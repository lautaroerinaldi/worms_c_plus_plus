#include "VerificadorAreaMundo.h"

#include "modelo/CuerpoMundo.h"
#include "modelo/Viga.h"
#include "modelo/CodigosModelo.h"

VerificadorAreaMundo::VerificadorAreaMundo() {
}

VerificadorAreaMundo::~VerificadorAreaMundo() {
}

bool VerificadorAreaMundo::ReportFixture(b2Fixture* fixture) {
	b2Body* body = fixture->GetBody();
	CuerpoMundo* cuerpo = (CuerpoMundo*) body->GetUserData();
	if ((cuerpo->obtenerTipo() == VIGA) || (cuerpo->obtenerTipo() == BORDE)){
		this->cuerposEncontrados.push_back(body);
	}
	return true;
}

std::vector<b2Body*>& VerificadorAreaMundo::obtenerCuerpos() {
	return this->cuerposEncontrados;
}

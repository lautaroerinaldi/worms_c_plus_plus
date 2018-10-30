#include "modelo/extensionBox2D/ObservadorContactos.h"

#include "comun/Codigos.h"
#include "modelo/CodigosModelo.h"
#include "modelo/CuerpoMundo.h"
#include "modelo/Gusano.h"
#include "modelo/Viga.h"
#include "modelo/Bala.h"

ObservadorContactos::ObservadorContactos() {
}

ObservadorContactos::~ObservadorContactos() {
}

void ObservadorContactos::BeginContact(b2Contact* contact) {
	//Obtengo los cuerpos de contacto
	b2Body* cuerpo1 = contact->GetFixtureA()->GetBody();
	b2Body* cuerpo2 = contact->GetFixtureB()->GetBody();
	CuerpoMundo* cuerpo1_data = (CuerpoMundo*) cuerpo1->GetUserData();
	CuerpoMundo* cuerpo2_data = (CuerpoMundo*) cuerpo2->GetUserData();
	if ((cuerpo1_data != NULL) && (cuerpo2_data != NULL)){
		//Colision gusano con viga
		if ((cuerpo1_data->obtenerTipo() == GUSANO) &&
				(cuerpo2_data->obtenerTipo() == VIGA)){
			Gusano* gusano = (Gusano*)cuerpo1_data;
			Viga* viga = (Viga*) cuerpo2_data;
			gusano->aterrizar(viga->obtenerAngulo());
		}
		if ((cuerpo2_data->obtenerTipo() == GUSANO) &&
				(cuerpo1_data->obtenerTipo() == VIGA)){
			Gusano* gusano = (Gusano*)cuerpo2_data;
			Viga* viga = (Viga*) cuerpo1_data;
			gusano->aterrizar(viga->obtenerAngulo());
		}
		//Colision gusano con agua
		if ((cuerpo1_data->obtenerTipo() == GUSANO) &&
				(cuerpo2_data->obtenerTipo() == AGUA)){
			Gusano* gusano = (Gusano*)cuerpo1_data;
			gusano->morir();
		}
		if ((cuerpo2_data->obtenerTipo() == GUSANO) &&
				(cuerpo1_data->obtenerTipo() == AGUA)){
			Gusano* gusano = (Gusano*)cuerpo2_data;
			gusano->morir();
		}
		//Colision bala
		if ((cuerpo1_data->obtenerTipo() == BALA)){
			Bala* bala = (Bala*) cuerpo1_data;
			if (cuerpo2_data->obtenerTipo() != GUSANO){
				if (!bala->tieneRebote() && (!bala->tieneContador())){
					bala->marcarParaDetener();
				} else if (bala->tieneContador() && !bala->tieneRebote()){
					bala->frenarImpulso();
				}
			} else {
				Gusano* gusano = (Gusano*) cuerpo2_data;
				if (gusano->obtenerID() != bala->obtenerIDGusano()){
					bala->daniarGusano(gusano);
				}
			}
		}
		if (cuerpo2_data->obtenerTipo() == BALA){
			Bala* bala = (Bala*) cuerpo2_data;
			if (cuerpo1_data->obtenerTipo() != GUSANO){
				if (!bala->tieneRebote() && (!bala->tieneContador())){
					bala->marcarParaDetener();
				} else if (bala->tieneContador() && !bala->tieneRebote()){
					bala->frenarImpulso();
				}
			} else {
				Gusano* gusano = (Gusano*) cuerpo1_data;
				if (gusano->obtenerID() != bala->obtenerIDGusano()){
					bala->daniarGusano(gusano);
				}
			}
		}
	}
}

void ObservadorContactos::EndContact(b2Contact* contact) {
	//Obtengo los cuerpos de contacto
	b2Body* cuerpo1 = contact->GetFixtureA()->GetBody();
	b2Body* cuerpo2 = contact->GetFixtureB()->GetBody();
	CuerpoMundo* cuerpo1_data = (CuerpoMundo*) cuerpo1->GetUserData();
	CuerpoMundo* cuerpo2_data = (CuerpoMundo*) cuerpo2->GetUserData();
	if ((cuerpo1_data != NULL) && (cuerpo2_data != NULL)){
		//Colision gusano con viga
		if ((cuerpo1_data->obtenerTipo() == GUSANO) &&
				(cuerpo2_data->obtenerTipo() == VIGA)){
			Gusano* gusano = (Gusano*)cuerpo1_data;
			gusano->despegar();
		}
		if ((cuerpo2_data->obtenerTipo() == GUSANO) &&
				(cuerpo1_data->obtenerTipo() == VIGA)){
			Gusano* gusano = (Gusano*)cuerpo2_data;
			gusano->despegar();
		}
	}
}

void ObservadorContactos::PreSolve(b2Contact* contact, const b2Manifold*) {
	b2Body* cuerpo1 = contact->GetFixtureA()->GetBody();
	b2Body* cuerpo2 = contact->GetFixtureB()->GetBody();
	CuerpoMundo* cuerpo1_data = (CuerpoMundo*) cuerpo1->GetUserData();
	CuerpoMundo* cuerpo2_data = (CuerpoMundo*) cuerpo2->GetUserData();
	if ((cuerpo1_data != NULL) && (cuerpo2_data != NULL)){
		//Colision de gusano con los bordes
		if ((cuerpo1_data->obtenerTipo() == GUSANO) &&
				(cuerpo2_data->obtenerTipo() == BORDE)){
			Gusano* gusano = (Gusano*) cuerpo1_data;
			b2Vec2 posBorde = cuerpo2->GetPosition();
			b2Vec2 velGusano = cuerpo1->GetLinearVelocity();
			if (gusano->obtenerEstado() == VOLANDO){
				contact->SetRestitution(REBOTE_GUSANO);
			} else if (((posBorde.x < 0) && (velGusano.x < 0)) ||
					((posBorde.x > 0) && (velGusano.x > 0))){
				gusano->choco();
			}
		}
		if ((cuerpo2_data->obtenerTipo() == GUSANO) &&
				(cuerpo1_data->obtenerTipo() == BORDE)){
			Gusano* gusano = (Gusano*) cuerpo2_data;
			b2Vec2 posBorde = cuerpo1->GetPosition();
			b2Vec2 velGusano = cuerpo2->GetLinearVelocity();
			if (gusano->obtenerEstado() == VOLANDO){
				contact->SetRestitution(REBOTE_GUSANO);
			} else if (((posBorde.x < 0) && (velGusano.x < 0)) ||
					((posBorde.x > 0) && (velGusano.x > 0))){
				gusano->choco();
			}
		}
	}
}

void ObservadorContactos::PostSolve(b2Contact* contact,
		const b2ContactImpulse*) {
	b2Body* cuerpo1 = contact->GetFixtureA()->GetBody();
	b2Body* cuerpo2 = contact->GetFixtureB()->GetBody();
	CuerpoMundo* cuerpo1_data = (CuerpoMundo*) cuerpo1->GetUserData();
	CuerpoMundo* cuerpo2_data = (CuerpoMundo*) cuerpo2->GetUserData();
	if ((cuerpo1_data != NULL) && (cuerpo2_data != NULL)){
		//Colision de gusano con los bordes
		if ((cuerpo1_data->obtenerTipo() == GUSANO) &&
				(cuerpo2_data->obtenerTipo() == BORDE)){
			Gusano* gusano = (Gusano*) cuerpo1_data;
			if (gusano->obtenerEstado() == VOLANDO){
				contact->SetRestitution(0.0f);
			}
		}
		if ((cuerpo2_data->obtenerTipo() == GUSANO) &&
				(cuerpo1_data->obtenerTipo() == BORDE)){
			Gusano* gusano = (Gusano*) cuerpo2_data;
			if (gusano->obtenerEstado() == VOLANDO){
				contact->SetRestitution(0.0f);
			}
		}
	}
}

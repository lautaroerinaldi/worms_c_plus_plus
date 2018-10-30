#include "BateDeBaseball.h"

#include <math.h>
#include <list>

BateDeBaseball::BateDeBaseball() {
	this->municiones_infinitas = true;
	this->danio = 10;
}

BateDeBaseball::~BateDeBaseball() {
}

void BateDeBaseball::disparar(Escenario& escenario, Gusano& gusano,
		const int direccion, float angulo) {
	angulo *= -1.0f;
	float magnitud_impulso = 0.5f;
	//Armo la fuerza a aplicar acorde al angulo, direccion y magnitud de daño
	b2Vec2 impulso(magnitud_impulso * cos(angulo),
			magnitud_impulso * sin(angulo));
	if (direccion == IZQUIERDA){
		impulso.x *= -1.0f;
	}
	std::list<Gusano*> gusanos_cercanos;
	escenario.obtenerGusanosCercanos(gusano, direccion, gusanos_cercanos);
	if(!gusanos_cercanos.empty()){
		std::list<Gusano*>::iterator it = gusanos_cercanos.begin();
		for (; it != gusanos_cercanos.end(); it++){
			Gusano* gusano_enemigo = (*it);
			if (!(gusano_enemigo->obtenerID() == gusano.obtenerID())){
				gusano_enemigo->restarVida(this->danio);
				b2Vec2 punto_impacto;
				punto_impacto.x = 0;
				punto_impacto.y = TAM_GUSANO_EN_METROS / 2;
				if (direccion == IZQUIERDA){
					punto_impacto.x = TAM_GUSANO_EN_METROS;
				}
				impulso *= gusano_enemigo->obtenerCuerpo()->GetMass();
				gusano_enemigo->recibirImpulso(impulso,punto_impacto);
			}
		}
	}
}

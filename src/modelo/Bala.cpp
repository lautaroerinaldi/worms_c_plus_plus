#include "modelo/Bala.h"
#include "comun/Codigos.h"

Bala::Bala(const int id, const int tipoB, b2Vec2 posicion, const float angulo,
		const int direccion, const int conteo, const bool fragmentar,
		const bool rebota, const int id_gusano) : CuerpoMundo(BALA) {
	this->id = id;
	this->posicion = posicion;
	this->angulo = angulo * (-1);
	this->direccion = direccion;
	this->danio = 0;
	this->radio = 0;
	this->cuerpo = NULL;
	this->exploto = false;
	this->id_gusano = id_gusano;
	this->viento = 0;
	this->dentenido = false;
	this->cuenta_regresiva = conteo;
	this->lanza_fragmentos = fragmentar;
	this->rebota = rebota;
	this->tipo_bala = tipoB;
}

Bala::~Bala() {
}

void Bala::configurarDanio(const int danio, const int radio) {
	this->danio = danio;
	this->radio = radio;
}

int Bala::obtenerID() {
	return this->id;
}

int Bala::obtenerTipoBala(){
	return this->tipo_bala;
}

int Bala::obtenerIDGusano() {
	return this->id_gusano;
}

void Bala::agregarCuerpo(b2Body* cuerpo) {
	this->cuerpo = cuerpo;
}

b2Body* Bala::obtenerCuerpo() {
	return this->cuerpo;
}

bool Bala::cambioPosicion() {
	if (this->cuerpo != NULL){
		int x_pos = this->posicion.x * FACTOR_ESCALA_DE_MODELO_A_VISTA;
		int y_pos = this->posicion.y * FACTOR_ESCALA_DE_MODELO_A_VISTA;
		int c_x_pos = this->cuerpo->GetPosition().x *
				FACTOR_ESCALA_DE_MODELO_A_VISTA;
		int c_y_pos = this->cuerpo->GetPosition().y *
				FACTOR_ESCALA_DE_MODELO_A_VISTA;
		if ((x_pos == c_x_pos) && (y_pos == c_y_pos)){
			return false;
		}
		return true;
	}
	return false;
}

b2Vec2 Bala::obtenerPosicion() {
	if (this->cuerpo != NULL){
		this->posicion = this->cuerpo->GetPosition();
	}
	return this->posicion;
}

float Bala::obtenerAngulo() {
	if (this->cuerpo != NULL){
		this->angulo = this->cuerpo->GetAngle();
		if (this->direccion == IZQUIERDA){
			this->angulo *= (-1.0f);
		}
	}
	return this->angulo;
}

int Bala::obtenerDireccion() {
	return this->direccion;
}

int Bala::obtenerRadio() {
	return this->radio;
}


void Bala::agregarViento(const float viento) {
	this->viento = viento;
}

void Bala::impulsar(const int potencia) {
	float impulso_mag = 1;
	b2Vec2 impulso(impulso_mag * cos(this->angulo),
			impulso_mag * sin(this->angulo));
	if (this->direccion == IZQUIERDA){
		impulso.x *= -1.0f;
	}
	if (potencia != 0){
		impulso.x *= potencia;
		impulso.y *= potencia;
	}
	if (viento != 0){
		impulso.x += viento;
	}
	if (this->cuenta_regresiva != 0){
		iniciaCronometro();
	}
	this->cuerpo->ApplyLinearImpulseToCenter(impulso,true);
}

void Bala::frenarImpulso() {
	this->cuerpo->SetLinearVelocity(b2Vec2(0,0));
}

void Bala::explotar() {
	std::chrono::high_resolution_clock::time_point tiempo_actual =
			std::chrono::high_resolution_clock::now();
	int tiempo_transcurrido =
			std::chrono::duration_cast<std::chrono::seconds>
	(tiempo_actual - this->tiempo_inicio).count();
	if (tiempo_transcurrido >= this->cuenta_regresiva){
		b2CircleShape formaExplosion;
		formaExplosion.m_p.Set(TAM_BALA_EN_METROS/2,TAM_BALA_EN_METROS/2);
		formaExplosion.m_radius = this->radio;
		b2FixtureDef fixtureExplosion;
		fixtureExplosion.shape = &formaExplosion;
		fixtureExplosion.filter.categoryBits = CAT_BALA;
		fixtureExplosion.filter.maskBits = CAT_GUSANO;
		this->cuerpo->CreateFixture(&fixtureExplosion);
		this->exploto = true;
	}
}

void Bala::marcarParaDetener() {
	this->dentenido = true;
}

bool Bala::seMarcoParaDetener() {
	return this->dentenido;
}

void Bala::detener() {
	this->cuerpo->SetAwake(false);
}

void Bala::iniciaCronometro() {
	this->tiempo_inicio = std::chrono::high_resolution_clock::now();
}

bool Bala::yaExploto() {
	return this->exploto;
}

void Bala::daniarGusano(Gusano* gusano) {
	//Calculo distancia desde el centro del gusano hasta el centro de la bala
	b2Vec2 centro_explosion = this->posicion;
	centro_explosion.x += TAM_BALA_EN_METROS / 2.0f;
	centro_explosion.y += TAM_BALA_EN_METROS / 2.0f;
	b2Vec2 posicion_gusano = gusano->obtenerPosicion();
	posicion_gusano.x += TAM_GUSANO_EN_METROS / 2.0f;
	posicion_gusano.y += TAM_GUSANO_EN_METROS / 2.0f;
	b2Vec2 direccion_impacto = posicion_gusano - centro_explosion;
	float distancia = direccion_impacto.Normalize();
	if (distancia <= 1){
		gusano->restarVida(this->danio);
	} else {
		gusano->restarVida(this->danio / distancia);
	}
	if (distancia != 0){
		b2Vec2 punto_impacto = posicion_gusano;
		if (direccion_impacto.x > 0){
			punto_impacto.x -= TAM_GUSANO_EN_METROS / 2.0f;
		} else {
			punto_impacto.x += TAM_GUSANO_EN_METROS / 2.0f;
		}
		float magnitud_impulso = 1.0f / distancia;
		b2Vec2 impulso = magnitud_impulso * direccion_impacto;
		gusano->recibirImpulso(impulso,punto_impacto);
	}
}

bool Bala::estaDetenida() {
	return !this->cuerpo->IsAwake();
}

bool Bala::tieneContador(){
	return (this->cuenta_regresiva != 0);
}

bool Bala::debeFragmentarse() {
	return this->lanza_fragmentos;
}

bool Bala::tieneRebote() {
	return this->rebota;
}

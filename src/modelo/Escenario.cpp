#include "../modelo/Escenario.h"

#include "Box2D/Box2D.h"
#include "comun/Codigos.h"
#include "../modelo/CodigosModelo.h"
#include "../modelo/CuerpoMundo.h"
#include "../modelo/Gusano.h"
#include "../modelo/Viga.h"
#include "extensionBox2D/VerificadorAreaMundo.h"
#include "extensionBox2D/VerificadorRayo.h"

Escenario::Escenario() :
		mundo(GRAVEDAD), agua(AGUA), borde(BORDE) {
	this->dim_x = ANCHO_ESCENARIO;
	this->dim_y = ALTURA_ESCENARIO;
	//Genero valor aleatorio de viento (entre 0.2 y 10)
	srand (time(0));
	int num_aleatorio = rand() % 99 + 2;
	this->viento = num_aleatorio / 100.0f;
	//Le agrego aleatoriamente la direccion
	num_aleatorio = rand() % 2;
	if (num_aleatorio == 0){
		this->viento *= -1.0f;
	}
	//Creo bordes en el escenario
	armarBordes();
	//Creo la zona de agua al final del escenario
	b2BodyDef aguaDef;
	aguaDef.type = b2_staticBody;
	aguaDef.position.Set(this->dim_x / 2.0f,
			this->dim_y - ALTURA_AGUA_EN_METROS / 2.0f);
	aguaDef.userData = &this->agua;
	b2Body* cuerpoAgua = this->mundo.CreateBody(&aguaDef);
	b2PolygonShape formaAgua;
	formaAgua.SetAsBox(this->dim_x / 2.0f, ALTURA_AGUA_EN_METROS / 2.0f);
	b2FixtureDef aguaFixture;
	aguaFixture.shape = &formaAgua;
	aguaFixture.density = 0.0f;
	aguaFixture.filter.categoryBits = CAT_AGUA;
	cuerpoAgua->CreateFixture(&aguaFixture);
	//Asigno el observador al mundo
	this->mundo.SetContactListener(&this->observador_contactos);
}

Escenario::~Escenario() {
}

void Escenario::insertarViga(Viga& viga) {
	b2Vec2 pos = viga.obtenerPosicionInicial();
	float longitud = viga.obtenerLongitud();
	float angulo = viga.obtenerAngulo();
	b2BodyDef vigaDef;
	vigaDef.type = b2_staticBody;
	vigaDef.position.Set(pos.x, pos.y);
	vigaDef.angle = 0;
	vigaDef.userData = &viga;
	b2Body* cuerpoViga = this->mundo.CreateBody(&vigaDef);
	b2PolygonShape formaViga;
	b2Vec2 centro;
	centro.x = longitud / 2.0f;
	centro.y = ALTURA_VIGA_EN_METROS / 2.0f;
	formaViga.SetAsBox(longitud / 2.0f, ALTURA_VIGA_EN_METROS / 2.0f,centro,
			angulo);
	b2FixtureDef vigaFixture;
	vigaFixture.shape = &formaViga;
	vigaFixture.density = 0.0f;
	if (((angulo <= RAD_45) && (angulo != 0)) ||
			((angulo != b2_pi) && (angulo >= RAD_135))){
		vigaFixture.friction = FRICCION_VIGA;
	} else {
		vigaFixture.friction = 0.01f;
	}
	vigaFixture.filter.categoryBits = CAT_VIGA;
	cuerpoViga->CreateFixture(&vigaFixture);
	pos = cuerpoViga->GetPosition();
}

void Escenario::insertarGusano(Gusano& gusano) {
	b2Vec2 pos = gusano.obtenerPosicion();
	b2BodyDef gusanoDef;
	gusanoDef.type = b2_dynamicBody;
	gusanoDef.position = pos;
	gusanoDef.userData = &gusano;
	gusanoDef.bullet = true;
	b2Body* cuerpoGusano = this->mundo.CreateBody(&gusanoDef);
	cuerpoGusano->SetFixedRotation(true);
	b2Vec2 centro;
	centro.x = TAM_GUSANO_EN_METROS / 2.0f;
	centro.y = TAM_GUSANO_EN_METROS / 2.0f;
	b2CircleShape formaGusano;
	formaGusano.m_p.Set(centro.x,centro.y);
	formaGusano.m_radius = TAM_GUSANO_EN_METROS / 2.0f;
	b2FixtureDef gusanoFixture;
	gusanoFixture.shape = &formaGusano;
	gusanoFixture.density = DENSIDAD_GUSANO;
	gusanoFixture.friction = FRICCION_GUSANO;
	gusanoFixture.filter.categoryBits = CAT_GUSANO;
	gusanoFixture.filter.maskBits = CAT_BORDE | CAT_AGUA | CAT_VIGA | CAT_BALA;
	cuerpoGusano->CreateFixture(&gusanoFixture);
	gusano.agregarCuerpo(cuerpoGusano);
}


void Escenario::agregarBala(Bala& bala, bool viento, bool rebote) {
	b2Vec2 posicion = bala.obtenerPosicion();
	b2BodyDef balaDef;
	balaDef.type = b2_dynamicBody;
	balaDef.position = posicion;
	balaDef.userData = &bala;
	balaDef.bullet = true;
	b2Body* cuerpoBala = this->mundo.CreateBody(&balaDef);
	b2CircleShape formaBala;
	b2Vec2 centro(TAM_BALA_EN_METROS / 2.0f, TAM_BALA_EN_METROS / 2.0f);
	formaBala.m_p.Set(centro.x,centro.y);
	formaBala.m_radius = TAM_BALA_EN_METROS / 2.0f;
	b2FixtureDef balaFixture;
	balaFixture.shape = &formaBala;
	balaFixture.density = 2.0f;
	if (rebote){
		balaFixture.restitution = 0.1f;
	}
	balaFixture.filter.categoryBits = CAT_BALA;
	balaFixture.filter.maskBits = CAT_BORDE | CAT_AGUA | CAT_VIGA;
	cuerpoBala->CreateFixture(&balaFixture);
	bala.agregarCuerpo(cuerpoBala);
	if (viento){
		bala.agregarViento(this->viento);
	}
}

void Escenario::simularMundo() {
	this->mundo.Step(TIME_STEP, VEL_ITERATIONS, POS_ITERATIONS);
	this->mundo.ClearForces();
}

void Escenario::simularMundoCero() {
	this->mundo.Step(0, VEL_ITERATIONS, POS_ITERATIONS);
	this->mundo.ClearForces();
}

void Escenario::removerGusano(Gusano& gusano) {
	gusano.obtenerCuerpo()->SetActive(false);
}

void Escenario::removerBala(Bala& bala) {
	bala.obtenerCuerpo()->SetActive(false);
}

bool Escenario::posicionLibre(b2Vec2 posicion) {
	VerificadorAreaMundo verificador;
	b2AABB aabb;
	aabb.upperBound = posicion;
	aabb.lowerBound.x = posicion.x + TAM_GUSANO_EN_METROS;
	aabb.lowerBound.y = posicion.y + TAM_GUSANO_EN_METROS;
	this->mundo.QueryAABB(&verificador, aabb);
	std::vector<b2Body*>& cuerpos = verificador.obtenerCuerpos();
	if (cuerpos.empty()){
		return true;
	}
	return false;
}

void Escenario::obtenerGusanosCercanos(Gusano& gusano, const int direccion,
		std::list<Gusano*>& gusanos_cercanos) {
	VerificadorRayo raycastCallback(gusanos_cercanos);
	//Posicion inical del rayo
	b2Vec2 pos_inicial = gusano.obtenerPosicion();
	pos_inicial.y += TAM_GUSANO_EN_METROS / 2;
	if (direccion == IZQUIERDA){
		pos_inicial.x += TAM_GUSANO_EN_METROS;
	}
	//Posicion final del rayo
	b2Vec2 pos_final = pos_inicial;
	if (direccion == DERECHA){
		pos_final.x += 2 * TAM_GUSANO_EN_METROS;
	} else {
		pos_final.x -= 2 * TAM_GUSANO_EN_METROS;
	}
	this->mundo.RayCast(&raycastCallback,pos_inicial,pos_final);
}

float Escenario::obtenerViento() {
	return (this->viento * 10);
}

void Escenario::armarBordes() {
	//Borde superior:
	b2BodyDef bordeDef;
	bordeDef.position.Set(this->dim_x / 2.0f, -0.5f);
	bordeDef.userData = &this->borde;
	b2Body* cuerpoBorde = this->mundo.CreateBody(&bordeDef);
	b2PolygonShape formaBorde;
	formaBorde.SetAsBox(this->dim_x / 2.0f + 1.0f, 0.5f);
	b2FixtureDef bordeFixture;
	bordeFixture.shape = &formaBorde;
	bordeFixture.density = 0.0f;
	bordeFixture.filter.categoryBits = CAT_BORDE;
	cuerpoBorde->CreateFixture(&bordeFixture);
	//Borde derecho:
	bordeDef.position.Set(this->dim_x + 0.5f, this->dim_y / 2.0f);
	bordeDef.userData = &this->borde;
	cuerpoBorde = this->mundo.CreateBody(&bordeDef);
	formaBorde.SetAsBox(0.5f, this->dim_y / 2.0f);
	bordeFixture.shape = &formaBorde;
	cuerpoBorde->CreateFixture(&bordeFixture);
	//Borde izquierdo:
	bordeDef.position.Set(-0.5f, this->dim_y / 2.0f);
	bordeDef.userData = &this->borde;
	cuerpoBorde = this->mundo.CreateBody(&bordeDef);
	formaBorde.SetAsBox(0.5f, this->dim_y / 2.0f);
	bordeFixture.shape = &formaBorde;
	cuerpoBorde->CreateFixture(&bordeFixture);
	//Borde inferior:
	bordeDef.position.Set(this->dim_x / 2.0f + 1.0f, this->dim_y + 0.5f);
	bordeDef.userData = &this->borde;
	cuerpoBorde = this->mundo.CreateBody(&bordeDef);
	formaBorde.SetAsBox(this->dim_x / 2.0f + 2.0f, 0.5f);
	bordeFixture.shape = &formaBorde;
	cuerpoBorde->CreateFixture(&bordeFixture);
}


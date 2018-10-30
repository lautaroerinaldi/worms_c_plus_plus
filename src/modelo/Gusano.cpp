#include "modelo/Gusano.h"

#include "modelo/CuerpoMundo.h"
#include "comun/Codigos.h"
#include "CodigosModelo.h"

Gusano::Gusano(const int id, const int jugador, const float x, const float y,
		const int inclinacion, const int vida) : CuerpoMundo(GUSANO), posicion(x,y){
	this->id = id;
	this->id_jugador = jugador;
	this->cuerpo = NULL;
	this->inclinacion = inclinacion;
	this->vida = vida;
	this->activo = false;
	this->enContactoConSuelo = false;
	this->velocidadCaminata = b2Vec2(0.2f,0.0f);
	this->velocidadSalto = b2Vec2(1.0f,-0.5f);
	this->velocidadSaltoAtras = b2Vec2(0.2f,-1.2f);
	this->estado = CAYENDO;
	this->cambioDeEstado = false;
	this->altura_incio_caida = y;
	this->sufrio_danio = false;
	this->angulo_viga = 0;
}

Gusano::~Gusano() {
}

int Gusano::obtenerID() {
    return this->id;
}

int Gusano::obtenerIDJugador() {
    return this->id_jugador;
}

int Gusano::obtenerVida() {
    return this->vida;
}

int Gusano::obtenerInclinacion(){
	return this->inclinacion;
}

int Gusano::obtenerEstado() {
	return this->estado;
}

bool Gusano::cambioEstado() {
	if (this->cambioDeEstado){
		this->cambioDeEstado = false;
		return true;
	}
	return false;
}

bool Gusano::cambioPosicion() {
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
	if ((this->estado != QUIETO) && (this->estado != MUERTO)){
		this->estado = QUIETO;
		this->cambioDeEstado = true;
	}
	return false;
}

b2Vec2 Gusano::obtenerPosicion() {
    if (this->cuerpo != NULL) {
        this->posicion = this->cuerpo->GetPosition();
    }
    return this->posicion;
}

void Gusano::agregarCuerpo(b2Body* cuerpoGus) {
    this->cuerpo = cuerpoGus;
}

b2Body* Gusano::obtenerCuerpo() {
    return this->cuerpo;
}

void Gusano::sumarVida(int puntos) {
	this->vida += puntos;
}

void Gusano::restarVida(int puntos){
	this->vida -= puntos;
	if (this->vida <= 0){
            this->vida = 0;
		this->estado = MUERTO;
		this->cambioDeEstado = true;
	}
	this->sufrio_danio = true;
}

void Gusano::morir(){
	this->vida = 0;
	this->estado = MUERTO;
	this->cambioDeEstado = true;
}

bool Gusano::estaHerido(){
	if (this->sufrio_danio){
		this->sufrio_danio = false;
		return true;
	}
	return false;
}

void Gusano::frenar() {
    this->cuerpo->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
}

void Gusano::detener() {
    if ((this->estado != QUIETO) && (this->estado != MUERTO)){
    	if (this->enContactoConSuelo > 0){
    		this->estado = QUIETO;
    	} else {
    		this->estado = CAYENDO;
    	}
		this->cambioDeEstado = true;
    }
}

void Gusano::activar() {
	this->activo = true;
}

void Gusano::desactivar() {
	this->activo = false;
}

bool Gusano::estaActivo() {
	return this->activo;
}

bool Gusano::caminar(const int direccion) {
	if ((this->cuerpo != NULL) && (this->estado == QUIETO)) {
		this->cambioDeEstado = true;
		b2Vec2 velocidad;
		this->estado = CAMINANDO;
		velocidad = this->velocidadCaminata;
		if (direccion == IZQUIERDA) {
			velocidad.x *= -1.0f;
		}
		b2Vec2 impulso = this->cuerpo->GetMass() * velocidad;
		if ((this->angulo_viga != 0)){
			float angulo = this->angulo_viga;
			if (this->angulo_viga > RAD_90) {
				angulo -= b2_pi;
			}
			impulso.y = impulso.x * sin(angulo);
			impulso.x *= cos(angulo);
		}
		this->cuerpo->ApplyLinearImpulseToCenter(impulso,true);
		return true;
	}
	return false;
}

bool Gusano::saltar(const int direccion) {
	if ((this->cuerpo != NULL) && (this->estado == QUIETO)) {
		this->cambioDeEstado = true;
		b2Vec2 velocidad;
		this->estado = SALTANDO;
		velocidad = this->velocidadSalto;
		if (direccion == IZQUIERDA) {
			velocidad.x *= -1.0f;
		}
		b2Vec2 impulso = this->cuerpo->GetMass() * velocidad;
		this->cuerpo->ApplyLinearImpulseToCenter(impulso,true);
		return true;
	}
	return false;
}

bool Gusano::retroceder(const int direccion) {
	if ((this->cuerpo != NULL) && (this->estado == QUIETO)) {
		this->cambioDeEstado = true;
		b2Vec2 velocidad;
		this->estado = RETROCESO;
		velocidad = this->velocidadSaltoAtras;
		if (direccion == DERECHA) {
			velocidad.x *= -1.0f;
		}
		b2Vec2 impulso = this->cuerpo->GetMass() * velocidad;
		this->cuerpo->ApplyLinearImpulseToCenter(impulso,true);
		return true;
	}
	return false;
}

void Gusano::aterrizar(float angulo_viga) {
	if (this->enContactoConSuelo == 0){
		float altura_fin_caida = this->cuerpo->GetPosition().y;
		int diferencia = altura_fin_caida - this->altura_incio_caida;
		if (diferencia > 2){
			int danio;
			if((diferencia < 25)){
				danio = diferencia;
			} else {
				diferencia = 25;
			}
			restarVida(danio);
		}
		if (this->estado != MUERTO){
			frenar();
			this->estado = QUIETO;
			this->cambioDeEstado = true;
		}
	}
	this->enContactoConSuelo++;
	if ((angulo_viga == 0) || (angulo_viga == RAD_90)){
		this->inclinacion = NORMAL;
	} else if (angulo_viga < RAD_90){
		this->inclinacion = ABAJO;
	} else {
		this->inclinacion = ARRIBA;
	}
	this->angulo_viga = angulo_viga;
}

void Gusano::despegar() {
	this->enContactoConSuelo--;
	if (this->enContactoConSuelo == 0){
		this->altura_incio_caida = this->cuerpo->GetPosition().y;
		this->inclinacion = NORMAL;
		if ((this->estado != SALTANDO) && (this->estado != RETROCESO)
				&& (this->estado != MUERTO)){
			if (this->activo){
				this->estado = CAYENDO;
				this->cambioDeEstado = true;
			} else {
				this->estado = VOLANDO;
				this->cambioDeEstado = true;
			}
		}
	}
}

void Gusano::choco() {
	if ((this->activo) && (this->estado != MUERTO)){
		this->estado = CHOCANDO;
		this->cambioDeEstado = true;
	}
}

void Gusano::teletransportar(b2Vec2 posicion) {
	this->cuerpo->SetTransform(posicion,0.0f);
}

void Gusano::recibirImpulso(const b2Vec2 impulso, const b2Vec2 punto_impacto) {
	if (this->estado != MUERTO){
		this->cuerpo->ApplyLinearImpulse(impulso,
				this->cuerpo->GetWorldPoint(punto_impacto), true);
		this->estado = VOLANDO;
	}
}

#include "modelo/Modelo.h"
#include "modelo/Jugador.h"
#include "modelo/armas/Armas.h"
#include "modelo/Bala.h"
#include "modelo/IncluirProtocolo.h"

#include <vector>

Modelo::Modelo(int jugadores, Buzon<Mensaje>& buzon) :
		buzon(buzon) {
	this->num_jugadores = jugadores;
	this->contador_jugador = 1;
	this->contador_gusano = 1;
	this->id_gusano_activo = 0;
	this->id_jugador_activo = 0;
	this->tipo_arma_activa = SIN_ARMA;
	//Creacion de los jugadores
	for (int i = 1; i <= jugadores; i++) {
		this->jugadores.insert( { i, Jugador(i) });
	}
	this->num_balas = 0;
	this->contador_salto = 0;
}

Modelo::~Modelo() {
}

void Modelo::agregarViga(float lon, float angulo, float x, float y) {
	float angulo_rad = angulo * TO_RAD;
	this->vigas.push_back(Viga(lon, angulo_rad, x, y));
	this->escenario.insertarViga(this->vigas.back());
	CrearViga msj_viga(lon, x, y, angulo);
	this->buzon.agregarMensaje(msj_viga);
}

void Modelo::agregarGusano(float x, float y, int inclinacion) {
	agregarGusanoConVida(x,y,inclinacion,200);
}

void Modelo::agregarGusanoConVida(float x, float y, int inclinacion, int vida){
	int jugador_id = this->contador_jugador;
	int id = this->contador_gusano;
	this->gusanos.insert({id, Gusano(id, jugador_id, x, y, inclinacion, vida)});
	this->escenario.insertarGusano(this->gusanos.at(id));
	this->jugadores.at(jugador_id).asignarGusano(this->gusanos.at(id));
	if (this->contador_jugador == this->num_jugadores) {
		this->contador_jugador = 1;
	} else {
		this->contador_jugador++;
	}
	CrearGusano msj_gusano(id, jugador_id, this->gusanos.at(id).obtenerVida(),
			x, y, inclinacion);
	this->buzon.agregarMensaje(msj_gusano);
	this->contador_gusano++;
}

void Modelo::configurarArmas(std::map<int,int>& nuevas_municiones) {
	for (int i = 1; i <= this->num_jugadores; i++){
		this->jugadores.at(i).configurarInventario(nuevas_municiones);
	}
}

void Modelo::inicioPartida() {
	if (this->gusanos.size() % this->num_jugadores != 0) {
		//Suma vida a jugadores con menos gusanos
		for (int i = 2; i <= this->num_jugadores; i++) {
			if (jugadores.at(i).cantidadGusanos()
					< jugadores.at(1).cantidadGusanos()) {
				jugadores.at(i).sumarVidasAGusanos();
			}
		}
		//Envio actualizacion de las vidas:
		std::map<int,Gusano>::iterator it = gusanos.begin();
		for (; it != gusanos.end(); it++){
			Gusano& gusano = it->second;
			ActualizarVida msj(gusano.obtenerID(), gusano.obtenerVida(),
										gusano.obtenerInclinacion());
			this->buzon.agregarMensaje(msj);
		}
	}
	//Preparo los turnos
	this->turnos.configurarRonda(this->gusanos.size(),this->num_jugadores);
	//Empieza como activo el primer gusano
	this->turnos.iniciarPrimerTurno();
	this->id_gusano_activo = turnos.obtenerIDGusano();
	this->id_jugador_activo = turnos.obtenerIDJugador();
	this->gusanos.at(this->id_gusano_activo).activar();
	//Notifico el viento
	float viento = this->escenario.obtenerViento();
	if (viento >= 0){
		this->buzon.agregarMensaje(InformarViento(viento,DERECHA));
	} else {
		viento *= -1.0f;
		this->buzon.agregarMensaje(InformarViento(viento,IZQUIERDA));
	}
	//Realizo un paso de simulacion de escenario
	//para dejarlo en estado de equilibrio
	this->escenario.simularMundo();
	mostrarCambios();
}

bool Modelo::iniciarTurno() {
	bool iniciado = this->turnos.iniciarSiguiente();
	if (iniciado){
		gusanos.at(this->id_gusano_activo).desactivar();
		this->id_gusano_activo = turnos.obtenerIDGusano();
		this->id_jugador_activo = turnos.obtenerIDJugador();
		gusanos.at(this->id_gusano_activo).activar();
	}
	return iniciado;
}

int Modelo::obtenerEstadoDeTurno() {
	return this->turnos.obtenerEstado();
}

int Modelo::obtenerIDJugadorEnTurno() {
	return this->id_jugador_activo;
}

int Modelo::obtenerIDGusanoEnTurno() {
	return this->id_gusano_activo;
}

int Modelo::actualizar() {
	this->escenario.simularMundo();
	mostrarCambios();
	return this->turnos.controlFinTurnoPorTiempo();
}

void Modelo::moverGusano(const int id_g, const int direccion) {
	Gusano& gusano = gusanos.at(id_g);
	if (gusano.caminar(direccion)){
		escenario.simularMundo();
		gusano.frenar();
		mostrarCambios();
		gusano.detener();
	}
}

void Modelo::saltarGusano(const int id_g, const int direccion) {
	Gusano& gusano = gusanos.at(id_g);
	if (gusano.saltar(direccion)) {
		this->contador_salto = 1;
		escenario.simularMundo();
		mostrarCambios();
	}
}

void Modelo::saltarAtrasGusano(const int id_g, const int direccion) {
	Gusano& gusano = gusanos.at(id_g);
	if (gusano.retroceder(direccion)) {
		this->contador_salto = 1;
		escenario.simularMundo();
		mostrarCambios();
	}
}

void Modelo::mostrarCambios() {
	bool sin_cambios = true;
	//Cambios en los gusanos
	std::map<int, Gusano>::iterator it = this->gusanos.begin();
	for (; it != this->gusanos.end(); it++) {
		Gusano& gusano = it->second;
		bool cambio_pos = gusano.cambioPosicion();
		b2Vec2 pos = gusano.obtenerPosicion();
		if (cambio_pos) {
			if (gusano.obtenerEstado() == MUERTO){
				MoverGusano msj_mover(gusano.obtenerID(), pos.x, pos.y,
						gusano.obtenerInclinacion(),QUIETO);
				this->buzon.agregarMensaje(msj_mover);
			} else {
				MoverGusano msj_mover(gusano.obtenerID(), pos.x, pos.y,
						gusano.obtenerInclinacion(),gusano.obtenerEstado());
				this->buzon.agregarMensaje(msj_mover);
				if ((gusano.obtenerEstado() == SALTANDO) ||
						(gusano.obtenerEstado() == RETROCESO)){
					if (this->contador_salto == 10){
						gusano.frenar();
						gusano.detener();
						this->contador_salto = 0;
					} else {
						this->contador_salto++;
					}
				}
			}
			sin_cambios = false;
		}
		if (gusano.cambioEstado()) {
			switch (gusano.obtenerEstado()) {
			case CHOCANDO:{
				MoverGusano msj_mover(gusano.obtenerID(), pos.x, pos.y,
						gusano.obtenerInclinacion(),gusano.obtenerEstado());
				this->buzon.agregarMensaje(msj_mover);
				gusano.detener();
				break;
			}
			case MUERTO:{
				ActualizarVida msj(gusano.obtenerID(), gusano.obtenerVida(),
									gusano.obtenerInclinacion());
				this->buzon.agregarMensaje(msj);
				escenario.removerGusano(gusano);
				turnos.removerGusano(gusano.obtenerID());
				if (gusano.estaActivo()){
					turnos.prepararFin();
				}
				break;
			}
			}
		} else {
			if ((gusano.obtenerEstado() == VOLANDO) && !cambio_pos){
				gusano.detener();
			}
		}
		if ((gusano.obtenerEstado() != MUERTO) && (gusano.estaHerido())) {
			ActualizarVida msj(gusano.obtenerID(), gusano.obtenerVida(),
					gusano.obtenerInclinacion());
			this->buzon.agregarMensaje(msj);
			if (gusano.estaActivo()){
				turnos.prepararFin();
			}
		}
	}
	//Cambios en las balas
	if (!this->balas.empty()){
		std::vector<int> balas_a_destruir;
		std::map<int, Bala>::iterator it_b = this->balas.begin();
		for (; it_b != this->balas.end(); it_b++){
			Bala& bala = it_b->second;
			if (bala.yaExploto()){
				DestruirBala msj(bala.obtenerID());
				this->buzon.agregarMensaje(msj);
				balas_a_destruir.push_back(it_b->first);
			} else {
				if (bala.cambioPosicion()){
					b2Vec2 pos = bala.obtenerPosicion();
					int angulo = 0;
					MoverBala msj(bala.obtenerID(), pos.x, pos.y, angulo,
							bala.obtenerDireccion());
					this->buzon.agregarMensaje(msj);
					sin_cambios = false;
				}
				if (bala.seMarcoParaDetener()){
					bala.detener();
					bala.explotar();
					sin_cambios = false;
				} else if (bala.tieneContador() && !bala.yaExploto()){
					bala.explotar();
					sin_cambios = false;
				}
				if (bala.yaExploto()){
					if (!bala.seMarcoParaDetener()){
						bala.detener();
					}
					//Para que se detecte la explosion
					this->escenario.simularMundoCero();
					b2Vec2 posicion_explosion = bala.obtenerPosicion();
					ImpactarBala msj(bala.obtenerID(),posicion_explosion.x,
							posicion_explosion.y,bala.obtenerRadio());
					this->buzon.agregarMensaje(msj);
					this->escenario.removerBala(bala);
					if (bala.debeFragmentarse()){
						std::vector<int> angulos{0,45,135,180,225,315};
						std::vector<int> direcciones{DERECHA,DERECHA,IZQUIERDA,
							IZQUIERDA,IZQUIERDA,DERECHA};
						int id_bala;
						int id_gusano = bala.obtenerIDGusano();
						b2Vec2 pos = posicion_explosion;
						int tipo_bala = bala.obtenerTipoBala();
						if (tipo_bala == GRANADA_ROJA){
							pos.y -= 0.1f;
							if (pos.x < 0.5f){
								pos.x += 0.1f;
							} else if (pos.x > ANCHO_ESCENARIO - 0.5f){
								pos.x -= 0.1f;
							}
						}
						for (int i = 0; i < 6; i++){
							this->num_balas++;
							id_bala = this->num_balas;
							this->balas.insert({id_bala, Bala(id_bala,
									tipo_bala, pos,	angulos.at(i) * TO_RAD,
									DERECHA, 0, false, false, id_gusano)});
							CrearBala msj_bala(id_bala, pos.x, pos.y,
									0, direcciones.at(i), tipo_bala);
							this->buzon.agregarMensaje(msj_bala);
							Bala& fragmento = this->balas.at(id_bala);
							fragmento.configurarDanio(10,2);
							this->escenario.agregarBala(fragmento,false,false);
							fragmento.impulsar(0);
						}
					}
				}
			}
		}
		if (!balas_a_destruir.empty()){
			for (unsigned int i = 0; i < balas_a_destruir.size(); i++){
				this->balas.erase(balas_a_destruir.at(i));
			}
		}
	}
	if ((turnos.obtenerEstado() == TERMINANDO) && sin_cambios){
		turnos.finalizar();
	}
}

void Modelo::cargarArma(const int tipo_arma) {
	if (jugadores.at(this->id_jugador_activo).puedeCargarArma(tipo_arma)) {
		CargarArma msj_arma(this->id_gusano_activo, tipo_arma);
		buzon.agregarMensaje(msj_arma);
		this->tipo_arma_activa = tipo_arma;
	} else {
		this->buzon.agregarMensaje(Notificacion(NOTIFICACION_AVISO,
				this->id_jugador_activo,
				"El arma elegida no tiene más municiones"));
		this->tipo_arma_activa = SIN_ARMA;
	}
}

void Modelo::disparar(const float angulo, const int direccion,
		const int potencia, const int conteo, const float x, const float y) {
	switch (this->tipo_arma_activa){
	case SIN_ARMA:{
		this->buzon.agregarMensaje(Notificacion(NOTIFICACION_AVISO,
				id_jugador_activo, "Debe cargar un arma antes de disparar."));
		break;
	}
	case BAZOOKA:{
		dispararBazooka(angulo, direccion, potencia);
		break;
	}
	case BANANA:{
		lanzarBanana(angulo, direccion, potencia, conteo);
		break;
	}
	case MORTERO:{
		lanzarMortero(angulo, direccion, potencia);
		break;
	}
	case GRANADA_ROJA:{
		lanzarGranadaRoja(angulo, direccion, potencia, conteo);
		break;
	}
	case GRANADA_VERDE:{
		lanzarGranadaVerde(angulo, direccion, potencia, conteo);
		break;
	}
	case GRANADA_SANTA:{
		lanzarGranadaSanta(angulo, direccion, potencia, conteo);
		break;
	}
	case DINAMITA:{
		dejarDinamita(conteo);
		break;
	}
	case ATAQUE_AEREO:{
		lanzarMisiles(b2Vec2(x,y));
		break;
	}
	case BATE_DE_BASEBALL:
		batear(direccion,angulo * TO_RAD);
		break;
	case TELETRANSPORTACION:{
		teletransportar(b2Vec2(x,y));
		break;
	}
	}
	this->turnos.prepararFin();
	this->tipo_arma_activa = SIN_ARMA;
}

void Modelo::eliminarJugador(const int id_jugador){
	this->jugadores.at(id_jugador).eliminar();
}

void Modelo::aplicar(SolicitarMover& mensaje) {
	moverGusano(this->id_gusano_activo, mensaje.getDireccion());
}

void Modelo::aplicar(SolicitarArma& mensaje) {
	cargarArma(mensaje.getTipoArma());
}

void Modelo::aplicar(SolicitarSaltar& mensaje) {
	saltarGusano(this->id_gusano_activo,mensaje.getDireccion());
}

void Modelo::aplicar(SolicitarRetroceso& mensaje) {
	saltarAtrasGusano(this->id_gusano_activo,mensaje.getDireccion());
}

void Modelo::aplicar(SolicitarAtacar& mensaje) {
	disparar(mensaje.getAnguloEnGrados(),mensaje.getDireccion(),
			mensaje.getPotencia(),mensaje.getConteo(),mensaje.getXModelo(),
			mensaje.getYModelo());
}

int Modelo::buscarGanador() {
	int contador = 0;
	int i = 1;
	while (i <= this->num_jugadores){
		if (this->jugadores.at(i).obtenerVida() > 0){
			contador++;
		}
		i++;
	}
	if (contador == 1){
		int jugador;
		i = 1;
		while (i <= this->num_jugadores){
			if (this->jugadores.at(i).obtenerVida() > 0){
				jugador = i;
			}
			i++;
		}
		return jugador;
	} else {
		return 0;
	}
}

void Modelo::teletransportar(b2Vec2 posicion) {
    Gusano& gusano = this->gusanos.at(this->id_gusano_activo);
    Teletransportador* teletransportador = (Teletransportador*)
			this->jugadores.at(this->id_jugador_activo).obtenerArma();
    if(teletransportador->disparar(this->escenario,gusano,posicion)){
    	this->buzon.agregarMensaje(TeletransportarGusano(
    			gusano.obtenerPosicion().x,	gusano.obtenerPosicion().y));
    } else {
    	this->buzon.agregarMensaje(Notificacion(NOTIFICACION_ERROR,
    		id_jugador_activo, "No se puede teletransportar a esa posicion"));
    }
}

void Modelo::batear(const int direccion, const float angulo) {
	BateDeBaseball* bate = (BateDeBaseball*)
		this->jugadores.at(this->id_jugador_activo).obtenerArma();
	bate->disparar(this->escenario, this->gusanos.at(this->id_gusano_activo),
			direccion, angulo);
	this->buzon.agregarMensaje(Atacar());
	actualizar();
}

void Modelo::dispararBazooka(const float angulo, const int direccion,
		const int potencia) {
	this->buzon.agregarMensaje(Atacar());
	Bazooka* bazooka = (Bazooka*)
			this->jugadores.at(this->id_jugador_activo).obtenerArma();
	this->num_balas++;
	int id_bala = this->num_balas;
	//Calculo la posicion de inicio de la bala
	Gusano& gusano = this->gusanos.at(this->id_gusano_activo);
	b2Vec2 posicion = gusano.obtenerPosicion();
	if (direccion == DERECHA){
		posicion.x += TAM_GUSANO_EN_METROS;
	}
	this->balas.insert({id_bala, Bala(id_bala, BAZOOKA, posicion,
			angulo * TO_RAD, direccion, 0, false, false,
			this->id_gusano_activo)});
	CrearBala msj_bala(id_bala, posicion.x, posicion.y, angulo, direccion,
			BAZOOKA);
	this->buzon.agregarMensaje(msj_bala);
	//Realizo el disparo
	Bala& bala = this->balas.at(id_bala);
	bazooka->disparar(bala, escenario, potencia);
}

void Modelo::lanzarMisiles(b2Vec2 posicion) {
	AtaqueAereo* avion = (AtaqueAereo*)
					this->jugadores.at(this->id_jugador_activo).obtenerArma();
	if (avion->tieneMuniciones()){
		this->buzon.agregarMensaje(Atacar());
		b2Vec2 misil_pos(posicion.x,0.3f);
		if (posicion.x <= 3 * TAM_BALA_EN_METROS){
			misil_pos.x = 0;
		} else if ((posicion.x > 3 * TAM_BALA_EN_METROS) &&
				(posicion.x < ANCHO_ESCENARIO - 3 * TAM_BALA_EN_METROS)){
			misil_pos.x -= 3 * TAM_BALA_EN_METROS;
		} else if (posicion.x >= ANCHO_ESCENARIO - 3 * TAM_BALA_EN_METROS){
			misil_pos.x -= 6 * TAM_BALA_EN_METROS;
		}
		std::vector<Bala*> misiles;
		for (int i = 0; i < 6; i++){
			this->num_balas++;
			int id_bala = this->num_balas;
			this->balas.insert({id_bala, Bala(id_bala, ATAQUE_AEREO, misil_pos,
					-b2_pi, DERECHA, 0, false, false, this->id_gusano_activo)});
			CrearBala msj_bala(id_bala, posicion.x, posicion.y, 270, DERECHA,
					ATAQUE_AEREO);
			this->buzon.agregarMensaje(msj_bala);
			misiles.push_back(&(this->balas.at(id_bala)));
			misil_pos.x += TAM_BALA_EN_METROS;
		}
		avion->disparar(this->escenario,misiles);
		this->escenario.simularMundo();
	} else {
		this->buzon.agregarMensaje(Notificacion(NOTIFICACION_AVISO,
				id_jugador_activo, "El arma no tiene más municiones"));
	}
}

void Modelo::lanzarGranadaVerde(const float angulo, const int direccion,
		const int potencia, int conteo) {
	this->buzon.agregarMensaje(Atacar());
	GranadaVerde* granada = (GranadaVerde*)
		this->jugadores.at(this->id_jugador_activo).obtenerArma();
	this->num_balas++;
	int id_bala = this->num_balas;
	//Calculo la posicion de inicio de la bala
	Gusano& gusano = this->gusanos.at(this->id_gusano_activo);
	b2Vec2 posicion = gusano.obtenerPosicion();
	if (direccion == DERECHA){
		posicion.x += TAM_GUSANO_EN_METROS;
	}
	if (conteo == 0){
		conteo = 5;
	}
	this->balas.insert({id_bala, Bala(id_bala, GRANADA_VERDE, posicion,
			angulo * TO_RAD, direccion, conteo, false, false,
			this->id_gusano_activo)});
	CrearBala msj_bala(id_bala, posicion.x, posicion.y, angulo,	direccion,
			GRANADA_VERDE);
	this->buzon.agregarMensaje(msj_bala);
	//Realizo el disparo
	Bala& bala = this->balas.at(id_bala);
	granada->disparar(bala, escenario, potencia);
}

void Modelo::lanzarGranadaSanta(const float angulo, const int direccion,
		const int potencia, int conteo) {
	GranadaSanta* granada = (GranadaSanta*)
					this->jugadores.at(this->id_jugador_activo).obtenerArma();
	if (granada->tieneMuniciones()){
		this->buzon.agregarMensaje(Atacar());
		this->num_balas++;
		int id_bala = this->num_balas;
		//Calculo la posicion de inicio de la bala
		Gusano& gusano = this->gusanos.at(this->id_gusano_activo);
		b2Vec2 posicion = gusano.obtenerPosicion();
		if (direccion == DERECHA){
			posicion.x += TAM_GUSANO_EN_METROS;
		}
		if (conteo == 0){
			conteo = 5;
		}
		this->balas.insert({id_bala, Bala(id_bala, GRANADA_SANTA, posicion,
				angulo * TO_RAD, direccion, conteo, false, false,
				this->id_gusano_activo)});
		CrearBala msj_bala(id_bala, posicion.x, posicion.y, angulo,	direccion,
				GRANADA_SANTA);
		this->buzon.agregarMensaje(msj_bala);
		//Realizo el disparo
		Bala& bala = this->balas.at(id_bala);
		granada->disparar(bala, escenario, potencia);
	} else {
		this->buzon.agregarMensaje(Notificacion(NOTIFICACION_AVISO,
				id_jugador_activo, "El arma no tiene más municiones"));
	}
}

void Modelo::dejarDinamita(int conteo) {
	Dinamita* dinamita = (Dinamita*)
			this->jugadores.at(this->id_jugador_activo).obtenerArma();
	if (dinamita->tieneMuniciones()){
		this->buzon.agregarMensaje(Atacar());
		this->num_balas++;
		int id_bala = this->num_balas;
		//Calculo la posicion de inicio de la bala
		Gusano& gusano = this->gusanos.at(this->id_gusano_activo);
		b2Vec2 posicion = gusano.obtenerPosicion();
		posicion.y += TAM_GUSANO_EN_METROS;
		posicion.x += TAM_GUSANO_EN_METROS / 2.0f;
		if (conteo == 0){
			conteo = 5;
		}
		this->balas.insert({id_bala, Bala(id_bala, DINAMITA, posicion, 90,
				DERECHA, conteo, false, false, this->id_gusano_activo)});
		CrearBala msj_bala(id_bala, posicion.x, posicion.y, 90,	DERECHA,
				DINAMITA);
		this->buzon.agregarMensaje(msj_bala);
		//Realizo el disparo
		Bala& bala = this->balas.at(id_bala);
		dinamita->disparar(bala, escenario);
	} else {
		this->buzon.agregarMensaje(Notificacion(NOTIFICACION_AVISO,
				id_jugador_activo, "El arma no tiene más municiones"));
	}
}

void Modelo::lanzarBanana(const float angulo, const int direccion,
		const int potencia, int conteo) {
	Banana* banana = (Banana*)
					this->jugadores.at(this->id_jugador_activo).obtenerArma();
	if (banana->tieneMuniciones()){
		this->buzon.agregarMensaje(Atacar());
		this->num_balas++;
		int id_bala = this->num_balas;
		//Calculo la posicion de inicio de la bala
		Gusano& gusano = this->gusanos.at(this->id_gusano_activo);
		b2Vec2 posicion = gusano.obtenerPosicion();
		if (direccion == DERECHA){
			posicion.x += TAM_GUSANO_EN_METROS;
		}
		if (conteo == 0){
			conteo = 5;
		}
		this->balas.insert({id_bala, Bala(id_bala, BANANA, posicion,
				angulo * TO_RAD, direccion, conteo, false, true,
				this->id_gusano_activo)});
		CrearBala msj_bala(id_bala, posicion.x, posicion.y, angulo,	direccion,
				BANANA);
		this->buzon.agregarMensaje(msj_bala);
		//Realizo el disparo
		Bala& bala = this->balas.at(id_bala);
		banana->disparar(bala, escenario, potencia);
	} else {
		this->buzon.agregarMensaje(Notificacion(NOTIFICACION_AVISO,
				id_jugador_activo, "El arma no tiene más municiones"));
	}
}

void Modelo::lanzarGranadaRoja(const float angulo, const int direccion,
		const int potencia, int conteo) {;
	GranadaRoja* granada = (GranadaRoja*)
					this->jugadores.at(this->id_jugador_activo).obtenerArma();
	if (granada->tieneMuniciones()){
		this->buzon.agregarMensaje(Atacar());
		this->num_balas++;
		int id_bala = this->num_balas;
		//Calculo la posicion de inicio de la bala
		Gusano& gusano = this->gusanos.at(this->id_gusano_activo);
		b2Vec2 posicion = gusano.obtenerPosicion();
		if (direccion == DERECHA){
			posicion.x += TAM_GUSANO_EN_METROS;
		}
		if (conteo == 0){
			conteo = 5;
		}
		this->balas.insert({id_bala, Bala(id_bala, GRANADA_ROJA, posicion,
				angulo * TO_RAD, direccion, conteo, true, false,
				this->id_gusano_activo)});
		CrearBala msj_bala(id_bala, posicion.x, posicion.y, angulo,	direccion,
				GRANADA_ROJA);
		this->buzon.agregarMensaje(msj_bala);
		//Realizo el disparo
		Bala& bala = this->balas.at(id_bala);
		granada->disparar(bala, escenario, potencia);
	} else {
		this->buzon.agregarMensaje(Notificacion(NOTIFICACION_AVISO,
				id_jugador_activo, "El arma no tiene más municiones"));
	}
}

void Modelo::lanzarMortero(const float angulo, const int direccion,
		const int potencia) {
	Mortero* mortero = (Mortero*)
			this->jugadores.at(this->id_jugador_activo).obtenerArma();
	if (mortero->tieneMuniciones()){
		this->buzon.agregarMensaje(Atacar());
		this->num_balas++;
		int id_bala = this->num_balas;
		//Calculo la posicion de inicio de la bala
		Gusano& gusano = this->gusanos.at(this->id_gusano_activo);
		b2Vec2 posicion = gusano.obtenerPosicion();
		if (direccion == DERECHA){
			posicion.x += TAM_GUSANO_EN_METROS;
		}
		this->balas.insert({id_bala, Bala(id_bala, MORTERO, posicion,
				angulo * TO_RAD, direccion, 0, true, false,
				this->id_gusano_activo)});
		CrearBala msj_bala(id_bala, posicion.x, posicion.y, angulo, direccion,
				MORTERO);
		this->buzon.agregarMensaje(msj_bala);
		//Realizo el disparo
		Bala& bala = this->balas.at(id_bala);
		mortero->disparar(bala, escenario, potencia);
	} else {
		this->buzon.agregarMensaje(Notificacion(NOTIFICACION_AVISO,
				id_jugador_activo, "El arma no tiene más municiones"));
	}
}

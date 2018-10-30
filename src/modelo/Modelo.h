#ifndef WORMS_SRC_MODEL_MODELO_H_
#define WORMS_SRC_MODEL_MODELO_H_

#include <list>
#include <map>

#include "Box2D/Box2D.h"

#include "modelo/CodigosModelo.h"
#include "modelo/Escenario.h"
#include "modelo/Gusano.h"
#include "modelo/Viga.h"
#include "modelo/Jugador.h"
#include "modelo/ManejadorDeTurnos.h"
#include "modelo/Bala.h"
#include "../comun/Buzon.h"
#include "../comun/Protocolo/Mensaje.h"
#include "../comun/Protocolo/Solicitudes/SolicitarArma.h"
#include "../comun/Protocolo/Solicitudes/SolicitarAtacar.h"
#include "../comun/Protocolo/Solicitudes/SolicitarMover.h"
#include "../comun/Protocolo/Solicitudes/SolicitarRetroceso.h"
#include "../comun/Protocolo/Solicitudes/SolicitarSaltar.h"

class Modelo {
	Buzon<Mensaje>& buzon;
	int num_jugadores;
	int num_balas;
	std::map<int, Jugador> jugadores;
	std::map<int, Gusano> gusanos;
	std::list<Viga> vigas;
	std::map<int, Bala> balas;
	Escenario escenario;
	int contador_jugador;
	int contador_gusano;
	int id_gusano_activo;
	int id_jugador_activo;
	int tipo_arma_activa;
	ManejadorDeTurnos turnos;
	int contador_salto;
public:
	//Constructor
	Modelo(int jugadores, Buzon<Mensaje>& buzon);
	//Destructor
	virtual ~Modelo();
	//Agrega vigas
	void agregarViga(float len, float a, float x, float y);
	//Agrega gusano
	void agregarGusano(float x, float y, int inclinacion);
	void agregarGusanoConVida(float x, float y, int inclinacion, int vida);
	//Configura las municiones de las armas
	void configurarArmas(std::map<int,int>& nuevas_municiones);
	//Iniciar Partida: Inicia el primer turno.
	void inicioPartida();
	//Iniciar siguiente turno
	bool iniciarTurno();
	//Obtener estado de turno
	int obtenerEstadoDeTurno();
	//Obtener id jugador en turno
	int obtenerIDJugadorEnTurno();
	//Obtener id de gusano en turno
	int obtenerIDGusanoEnTurno();
	//Actualizar Modelo (Mueve un paso a envia modificaciones)
	// Y retorna el tiempo en segundos que falta para que termine el turno.
	int actualizar();
	//Mover Gusano
	void moverGusano(const int id_g, const int direccion);
	//Saltar Gusano
	void saltarGusano(const int id_g, const int direccion);
	//Retroceso Gusano
	void saltarAtrasGusano(const int id_g, const int direccion);
	//Envia posiciones de gusanos si hubo cambios
	void mostrarCambios();
	//Verifica que el jugador puede cargar el arma
	void cargarArma(const int tipo_arma);
	//Disparar arma
	void disparar(const float angulo, const int direccion, const int potencia,
			const int conteo, const float x, const float y);
	//Elimina un jugador a pedido del servidor
	void eliminarJugador(const int id_jugador);
	//Buscar ganador: Si devuelve 0, no hay ganador todavía.
	//Si hay ganador devuelve el id
	int buscarGanador();
	//RECEPCION DE COMANDOS POR MENSAJE
	//Recepcion mensaje de movimiento
	void aplicar(SolicitarMover& mensaje);
	//Recepcion mensaje de salto
	void aplicar(SolicitarSaltar& mensaje);
	//Recepcion mensaje de salto
	void aplicar(SolicitarRetroceso& mensaje);
	//Recepcion mensaje de carga de arma
	void aplicar(SolicitarArma& mensaje);
	//Recepcion mensaje de solicitar atacar
	void aplicar(SolicitarAtacar& mensaje);
private:
	//Realiza el disparo del arma:
	void teletransportar(b2Vec2 posicion);
	void batear(const int direccion, const float angulo);
	void dispararBazooka(const float angulo, const int direccion,
			const int potencia);
	void lanzarMisiles(b2Vec2 posicion);
	void lanzarGranadaVerde(const float angulo, const int direccion,
			const int potencia, int conteo);
	void lanzarGranadaSanta(const float angulo, const int direccion,
			const int potencia, int conteo);
	void dejarDinamita(int conteo);
	void lanzarBanana(const float angulo, const int direccion,
			const int potencia, int conteo);
	void lanzarGranadaRoja(const float angulo, const int direccion,
			const int potencia, int conteo);
	void lanzarMortero(const float angulo, const int direccion,
			const int potencia);
};

#endif /* WORMS_SRC_MODEL_MODELO_H_ */

#ifndef WORMS_SRC_MODELO_MANEJADORDETURNOS_H_
#define WORMS_SRC_MODELO_MANEJADORDETURNOS_H_

#include <map>

#include <ctime>
#include <ratio>
#include <chrono>

class ManejadorDeTurnos {
	int cantidad_gusanos;
	std::map<int, int> gusanos; //Gusanos en ronda de turnos
	int id_gusano;
	int id_jugador;
	int estado;

	std::chrono::high_resolution_clock::time_point tiempo_de_inicio;

	void reiniciarTiempoDeInicio();
public:
	//Constructor:
	ManejadorDeTurnos();
	//Destructor
	virtual ~ManejadorDeTurnos();
	//Carga la informacion necesaria para manejar turnos
	void configurarRonda(const int cant_gusanos, const int cant_jugadores);
	//Devuelve el estado del turno
	int obtenerEstado();
	//Obtener id de gusano en turno
	int obtenerIDGusano();
	//Obtener id de jugador en turno
	int obtenerIDJugador();
	//Inicia primer turno
	void iniciarPrimerTurno();
	//Inicia el turno siguiente (devuelve el id del gusano en turno)
	//Devuelve true si pudo asignar un gusano,
	//sino false y deja al estado SIN_TURNO (no hay más gusanos vivos).
	bool iniciarSiguiente();
	//Quita un gusano de la ronda de turnos
	void removerGusano(const int id_gusano);
	//Marca la ocurrencia de un evento de fin de turno
	void prepararFin();
	//Marca finalizacion de turno
	void finalizar();
	// Controla si el tiempo desde que inició el turno supera la duración
	//estándar de un turno y en dicho caso, lo termina
	//(si no estaba ya TERMINANDO). Además, retorna el tiempo en segundos
	// para que termine el turno
	int controlFinTurnoPorTiempo();
};

#endif /* WORMS_SRC_MODELO_MANEJADORDETURNOS_H_ */

#ifndef WORMS_SRC_MODELO_BALA_H_
#define WORMS_SRC_MODELO_BALA_H_

#include "modelo/CuerpoMundo.h"
#include "modelo/CodigosModelo.h"
#include "modelo/Gusano.h"
#include "../Box2D/Box2D.h"

#include <chrono>

class Bala: public CuerpoMundo {
protected:
	int id;
	b2Vec2 posicion;
	float angulo;
	int direccion;
	int danio;
	int radio;
	b2Body* cuerpo;
	bool exploto;
	int id_gusano;
	bool dentenido;
	float viento;
	int cuenta_regresiva;
	std::chrono::high_resolution_clock::time_point tiempo_inicio;
	bool lanza_fragmentos;
	bool rebota;
	int tipo_bala;
public:
	//Constructor
	Bala(const int id, const int tipoB, b2Vec2 posicion, const float angulo,
			const int direccion, const int conteo, const bool fragmentar,
			const bool rebota, const int id_gusano);
	//Destructor
	virtual ~Bala();
	//Configura el danio segun el tipo de bala
	void configurarDanio(const int danio, const int radio);
	//Devuelve el id de la bala
	int obtenerID();
	//Devuelve el tipo de bala
	int obtenerTipoBala();
	//Agrega cuerpo de mundo Box2D
	void agregarCuerpo(b2Body* cuerpo);
	//Devuelve el cuerpo de mundo Box2D
	b2Body* obtenerCuerpo();
	//Verifica si cambio de posicion
	bool cambioPosicion();
	//Devuelve la posicion
	b2Vec2 obtenerPosicion();
	//Devuelve el angulo
	float obtenerAngulo();
	//Devuelve direccion
	int obtenerDireccion();
	//Devuelve el id del gusano que la lanzo
	int obtenerIDGusano();
	//Devuelve el radio de impacto
	int obtenerRadio();
	//Agrega valor de viento
	void agregarViento(const float viento);
	//Pone la bala en movimiento
	void impulsar(const int potencia);
	//Frenar impulso
	void frenarImpulso();
	//Marca para que la Bala se detenga
	void marcarParaDetener();
	//Verifica si se detuvo
	bool seMarcoParaDetener();
	//Detener bala
	void detener();
	//Iniciar conteo tiempo
	void iniciaCronometro();
	//Marcar explosion
	void explotar();
	//Verifica si exploto
	bool yaExploto();
	//Verifica si esta detenida
	bool estaDetenida();
	//Aplica daño al gusano pasado
	void daniarGusano(Gusano* gusano);
	//Indica si es de cuenta regresiva
	bool tieneContador();
	//Verifica si debe lanzar fragmentos
	bool debeFragmentarse();
	//Verifica si la bala rebota
	bool tieneRebote();
};

#endif /* WORMS_SRC_MODELO_BALA_H_ */

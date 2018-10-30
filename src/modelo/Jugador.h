#ifndef WORMS_SRC_MODELO_JUGADOR_H_
#define WORMS_SRC_MODELO_JUGADOR_H_

#include <map>
#include <string>

#include "modelo/CodigosModelo.h"
#include "modelo/Gusano.h"
#include "modelo/armas/ArmaGenerica.h"

class Jugador {
	int id;
	std::map<int,Gusano&> gusanos;
	std::map<int,ArmaGenerica> inventario;
	int tipo_arma_activa;
public:
	//Constructor
	explicit Jugador(const int id_jugador);
	//Destructor
	virtual ~Jugador();
	//Asigna un gusano al jugador
	void asignarGusano(Gusano& gusano);
	//Devuelve la cantidad de gusanos que tiene el jugador
	int cantidadGusanos();
	//Suma vidas a los gusanos del jugador
	void sumarVidasAGusanos();
	//Obtener id de jugador
	int obtenerID();
	//Devuelve la candidad de vida total del jugador (suma de los gusanos)
	int obtenerVida();
	//Configura las armas del jugador
	void configurarInventario(std::map<int,int>& nuevas_municiones);
	//Controla si puede cargar un arma
	bool puedeCargarArma(int tipo_arma);
	//Obtener el arma activa
	ArmaGenerica* obtenerArma();
	//Eliminar el jugador: mata a todos los gusanos del jugador
	void eliminar();
};

#endif /* WORMS_SRC_MODELO_JUGADOR_H_ */

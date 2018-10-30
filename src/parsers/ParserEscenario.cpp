#include "ParserEscenario.h"
#include "../modelo/Modelo.h"
#include "../comun/Codigos.h"
#include "../Yaml/yaml-cpp/yaml.h"

float ParserEscenario::convertirMagnitudVistaAModelo(int magnitud) {
	return ((float) magnitud / FACTOR_ESCALA_DE_MODELO_A_VISTA);
}

void ParserEscenario::levantarEscenario(Modelo& modelo,
		const std::string& nombre_archivo) {
	int vida;
	YAML::Node nodo_in = YAML::LoadFile(nombre_archivo);
	for (YAML::const_iterator it = nodo_in.begin(); it != nodo_in.end(); ++it) {
		if (it->first.as<std::string>() == "gusano") {
			YAML::Node nodo_gusano = nodo_in[it->first];
			modelo.agregarGusanoConVida(
					convertirMagnitudVistaAModelo(nodo_gusano["x"].as<int>()),
					convertirMagnitudVistaAModelo(nodo_gusano["y"].as<int>()),
					NORMAL, vida);
		} else if (it->first.as<std::string>() == "viga") {
			YAML::Node nodo_viga = nodo_in[it->first];
			modelo.agregarViga(nodo_viga["tamanio"].as<int>(),
					nodo_viga["angulo"].as<int>(),
					convertirMagnitudVistaAModelo(nodo_viga["x"].as<int>()),
					convertirMagnitudVistaAModelo(nodo_viga["y"].as<int>()));
		} else if (it->first.as<std::string>() == "municiones") {
			YAML::Node nodo_municiones = nodo_in[it->first];
			vida = nodo_municiones["vida"].as<int>();
			std::map<int,int> municiones;
			municiones.insert({ATAQUE_AEREO,nodo_municiones["aereo"].as<int>()});
			municiones.insert({BANANA,nodo_municiones["banana"].as<int>()});
			municiones.insert({BATE_DE_BASEBALL,nodo_municiones["bate"].as<int>()});
			municiones.insert({BAZOOKA,nodo_municiones["bazooka"].as<int>()});
			municiones.insert({DINAMITA,nodo_municiones["dinamita"].as<int>()});
			municiones.insert({GRANADA_ROJA,nodo_municiones["roja"].as<int>()});
			municiones.insert({GRANADA_VERDE,nodo_municiones["verde"].as<int>()});
			municiones.insert({GRANADA_SANTA,nodo_municiones["santa"].as<int>()});
			municiones.insert({MORTERO,nodo_municiones["mortero"].as<int>()});
			municiones.insert({TELETRANSPORTACION,nodo_municiones["teletransportacion"].as<int>()});
			modelo.configurarArmas(municiones);
		}
	}
}


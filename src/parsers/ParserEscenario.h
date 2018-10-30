#ifndef WORMS_SRC_PARSERS_PARSERESCENARIO_H_
#define WORMS_SRC_PARSERS_PARSERESCENARIO_H_

#include "../modelo/Modelo.h"

class ParserEscenario {
	//Convierte la magnitud de la vista al modelo
	float convertirMagnitudVistaAModelo(int magnitud);
public:
	//Parsea el archivo escenario y genera el modelo
	void levantarEscenario(Modelo& modelo, const std::string & nombre_archivo);
};

#endif /* WORMS_SRC_PARSERS_PARSERESCENARIO_H_ */

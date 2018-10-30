/*
 * CrearViga.h
 */

#ifndef SRC_COMUN_PROTOCOLO_ESCENARIO_CREARVIGA_H_
#define SRC_COMUN_PROTOCOLO_ESCENARIO_CREARVIGA_H_

#include "../Mensaje.h"
#include "../../DefinicionesPrivadas.h"
#include <string>

class CrearViga: public Mensaje {
	static destinatarios_posibles destinatarios;
	int longitud_en_metros;
	int x;
	int y;
	int angulo_en_grados;
	bool anguloEnGradosValido(int angulo_en_grados) const;
	float convertirARadianes(int angulo_en_grados) const;
	bool longitudVigaValida(float longitud_en_metros) const;
public:
	CrearViga(const std::string & comando_completo) throw (std::exception);
	CrearViga(float longitud, float x, float y, int angulo_en_grados);

	std::string serializar();
	destinatarios_posibles getDestinatariosSegunTipoMensaje() const;
	int getAnguloEnGrados() const;
	float getAnguloEnRadianes() const;
	int getLongitud() const;
	int getX() const;
	int getY() const;
};

#endif /* SRC_COMUN_PROTOCOLO_ESCENARIO_CREARVIGA_H_ */

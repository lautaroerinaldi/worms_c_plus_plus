/*
 * MoverGusano.h
 */

#ifndef COMUN_PROTOCOLO_MOVERGUSANO_H_
#define COMUN_PROTOCOLO_MOVERGUSANO_H_

#include "../Mensaje.h"

#include <exception>
#include <string>
#include <map>

class MoverGusano: public Mensaje {
protected:
	static destinatarios_posibles destinatarios;

	int id_gusano;
	int x;
	int y;
	int inclinacion;
	int estado_gusano;
	std::map<int, std::string> estados;

	bool inclinacionValida(int inclinacion);
	bool estadoGusanoValido(int estado_gusano);
	void inicializarEstados();
public:

	MoverGusano(const std::string & comando_completo) throw (std::exception);
	MoverGusano(int id_gusano, float x, float y, int inclinacion,
			int estado_gusano) throw (std::exception);

	std::string serializar();
	destinatarios_posibles getDestinatariosSegunTipoMensaje() const;

	int getIdGusano() const;
	int getInclinacion() const;
	int getX() const;
	int getY() const;

	int getEstadoGusano() const;
	std::string getEstadoToString() const;

	virtual ~MoverGusano();
};

#endif /* COMUN_PROTOCOLO_MOVERGUSANO_H_ */

/*
 * MoverPunteria.h
 */

#ifndef SRC_COMUN_PROTOCOLO_VISUALES_MOVERPUNTERIA_H_
#define SRC_COMUN_PROTOCOLO_VISUALES_MOVERPUNTERIA_H_

#include "../Mensaje.h"

#include <exception>
#include <string>

class MoverPunteria: public Mensaje {
	static destinatarios_posibles destinatarios;

	int punteria;
	bool punteriaValida(int punteria);
public:
	MoverPunteria(int punteria);
	MoverPunteria(const std::string & comando_completo) throw (std::exception);
	virtual ~MoverPunteria();
	int getPunteria() const;
	std::string serializar();

	destinatarios_posibles getDestinatariosSegunTipoMensaje() const;
};

#endif /* SRC_COMUN_PROTOCOLO_VISUALES_MOVERPUNTERIA_H_ */

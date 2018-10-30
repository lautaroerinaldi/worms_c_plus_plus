/*
 * DestruirBala.h
 */

#ifndef SRC_COMUN_PROTOCOLO_BALAS_DESTRUIRBALA_H_
#define SRC_COMUN_PROTOCOLO_BALAS_DESTRUIRBALA_H_

#include "../Mensaje.h"

#include <exception>
#include <string>

class DestruirBala: public Mensaje {
	static destinatarios_posibles destinatarios;

	int id_bala;
public:
	DestruirBala(const std::string & comando_completo) throw (std::exception);
	DestruirBala(int id_bala);

	virtual std::string serializar() const;
	destinatarios_posibles getDestinatariosSegunTipoMensaje() const;

	int getIdBala() const;

	virtual ~DestruirBala();
};

#endif /* SRC_COMUN_PROTOCOLO_BALAS_DESTRUIRBALA_H_ */

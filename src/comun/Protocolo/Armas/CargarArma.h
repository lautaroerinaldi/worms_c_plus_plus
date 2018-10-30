/*
 * CargarArma.h
 */

#ifndef COMUN_PROTOCOLO_CARGARARMA_H_
#define COMUN_PROTOCOLO_CARGARARMA_H_

#include "../Mensaje.h"

#include <exception>
#include <string>

class CargarArma: public Mensaje {
	static destinatarios_posibles destinatarios;

	int id_gusano;
	int tipo_arma;

	bool tipoArmaValida(int tipo_arma);
public:
	CargarArma(const std::string & comando_completo) throw (std::exception);
	CargarArma(int id_gusano, int tipo_arma) throw (std::exception);

	int getIdGusano() const;
	int getTipoArma() const;

	std::string serializar();
	destinatarios_posibles getDestinatariosSegunTipoMensaje() const;
};

#endif /* COMUN_PROTOCOLO_CARGARARMA_H_ */

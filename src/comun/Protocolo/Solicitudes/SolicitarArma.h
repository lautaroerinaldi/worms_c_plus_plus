/*
 * SolicitarArma.h
 */

#ifndef COMUN_PROTOCOLO_SOLICITARARMA_H_
#define COMUN_PROTOCOLO_SOLICITARARMA_H_

#include "../Mensaje.h"

#include <exception>
#include <string>

class SolicitarArma: public Mensaje {
	static destinatarios_posibles destinatarios;

	int tipo_arma;

	bool tipoArmaValida(int tipo_arma);
public:
	SolicitarArma(const std::string & comando_completo) throw (std::exception);
	SolicitarArma(int tipo_arma) throw (std::exception);
	std::string serializar() const;
	int getTipoArma() const;
	destinatarios_posibles getDestinatariosSegunTipoMensaje() const;
};

#endif /* COMUN_PROTOCOLO_SOLICITARARMA_H_ */

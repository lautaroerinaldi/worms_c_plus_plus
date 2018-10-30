/*
 * SolicitarAtacar.h
 */

#ifndef SRC_COMUN_PROTOCOLO_SOLICITUDES_SOLICITARATACAR_H_
#define SRC_COMUN_PROTOCOLO_SOLICITUDES_SOLICITARATACAR_H_

#include "../Mensaje.h"

#include <exception>
#include <string>

class SolicitarAtacar: public Mensaje {
	static destinatarios_posibles destinatarios;

	int angulo_en_grados;
	int direccion;
	int potencia;
	int conteo;
	int x_vista;
	int y_vista;

	bool direccionValida(int direccion);
public:
	SolicitarAtacar(const std::string & comando_completo) throw (std::exception);
	SolicitarAtacar(int angulo_en_grados, int direccion, int potencia,
			int conteo, int x_vista, int y_vista) throw (std::exception);

	virtual std::string serializar() const;
	destinatarios_posibles getDestinatariosSegunTipoMensaje() const;

	int getAnguloEnGrados() const;
	int getConteo() const;
	int getDireccion() const;
	int getPotencia() const;

	int getXVista() const;
	int getYVista() const;

	float getYModelo() const;
	float getXModelo() const;

	virtual ~SolicitarAtacar();
};

#endif /* SRC_COMUN_PROTOCOLO_SOLICITUDES_SOLICITARATACAR_H_ */

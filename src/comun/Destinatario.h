/*
 * Destinatario.h
 */

#ifndef SERVIDOR_DESTINATARIO_H_
#define SERVIDOR_DESTINATARIO_H_

class Mensaje;

class Destinatario {
protected:
	int id_jugador;
	int id_jugador_activo;
public:
	Destinatario();
	virtual void enviarMensaje(const Mensaje & mensaje) = 0;

	virtual ~Destinatario();

	// COPIAR Destinatario
	Destinatario(const Destinatario& otro) = delete;
	Destinatario& operator=(const Destinatario& otro) = delete;

	// MOVER Destinatario
	Destinatario(Destinatario&& otro) = delete;
	Destinatario& operator=(Destinatario&& otro) = delete;

	virtual void apagar() = 0;
	int getIdJugador() const;
	int getIdJugadorActivo() const;
	void setIdJugadorActivo(int id_jugador_activo);
	void setIdJugador(int id_jugador);
};

#endif /* SERVIDOR_DESTINATARIO_H_ */

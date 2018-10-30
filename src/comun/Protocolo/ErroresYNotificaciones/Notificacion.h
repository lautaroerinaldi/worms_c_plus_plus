/*
 * Notificacion.h
 */

#ifndef SRC_COMUN_PROTOCOLO_ERRORESYNOTIFICACIONES_NOTIFICACION_H_
#define SRC_COMUN_PROTOCOLO_ERRORESYNOTIFICACIONES_NOTIFICACION_H_

#include "../Mensaje.h"
#include <exception>

class Notificacion: public Mensaje {
	static destinatarios_posibles destinatarios;

	int tipo_notificacion;
	int id_jugador_destinatario;
	std::string notificacion;

	bool tipoNotificacionValida(int tipo_notificacion);
public:
	Notificacion(int tipo_notificacion, int id_jugador_destinatario,
			const std::string & notificacion) throw (std::exception);
	Notificacion(const std::string & comando_completo) throw (std::exception);

	std::string serializar() const;
	destinatarios_posibles getDestinatariosSegunTipoMensaje() const;

	int getTipoNotificacion() const;
	int getIdJugadorDestinatario() const;
	const std::string& getNotificacion() const;

	virtual ~Notificacion();
};

#endif /* SRC_COMUN_PROTOCOLO_ERRORESYNOTIFICACIONES_NOTIFICACION_H_ */

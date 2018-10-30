/*
 * ManejadorDeCliente.cpp
 */

#include "AdministradorDePartidas.h"
#include "Atlas.h"
#include "ManejadorDeCliente.h"
#include <iostream>
#include <map>
#include <sstream>

#include "../comun/Protocolo/Protocolo.h"
#include "../comun/Protocolo/ControlPartidas/CrearPartida.h"
#include "../comun/Protocolo/ControlPartidas/UnirseAPartida.h"
#include "../comun/DefinicionesDePrueba.h"

#include "../comun/Protocolo/NotificarIdPartida.h"
#include "../comun/Protocolo/NotificarIdJugador.h"

#include "../comun/Protocolo/Listas/ListaEscenarios.h"
#include "../comun/Protocolo/Listas/ListaPartidas.h"

#include "../comun/Protocolo/ErroresYNotificaciones/Notificacion.h"

int ManejadorDeCliente::cantidad_clientes_creados = 0;

ManejadorDeCliente::ManejadorDeCliente(SocketComunicador canal) :
		id(++ManejadorDeCliente::cantidad_clientes_creados), protocolo(
				std::move(canal)), activo(true), buzon(
		NULL), estado_partida(estados_posibles_T::partida_no_iniciada) {
	this->start();
}

bool ManejadorDeCliente::partidaNoIniciada() {
	return (activo
			&& (estado_partida == estados_posibles_T::partida_no_iniciada));
}

void ManejadorDeCliente::manejarPartidaNoIniciada() {

	std::map<std::string, comandos_logueo_posibles> comandos;
	comandos[CREAR_PARTIDA] = comandos_logueo_posibles::crear_partida;
	comandos[SOLICITAR_TODAS_LAS_PARTIDAS] =
			comandos_logueo_posibles::solicitar_todas_las_partidas;
	comandos[SOLICITAR_PARTIDAS_NO_INICIADAS] =
			comandos_logueo_posibles::solicitar_partidas_no_iniciadas;
	comandos[UNIRSE_A_PARTIDA] = comandos_logueo_posibles::unirse_a_partida;
	comandos[SOLICITAR_ESCENARIOS] =
			comandos_logueo_posibles::solicitar_escenarios;

	while (partidaNoIniciada()) {
		try {
			std::string mensaje(protocolo.recibirMensaje());

			if (mensaje == SALIR) {
				apagar();
				AdministradorDePartidas::getInstancia().salirDePartida(*this);
			} else {

				std::istringstream comando_completo(mensaje);
				std::string comando_a_pasar_provisorio(comando_completo.str());
				std::string sigla_comando("");
				comando_completo >> sigla_comando;

				try {
					switch (comandos.at(sigla_comando)) {
					case comandos_logueo_posibles::crear_partida: {
						int id_partida_creada =
								AdministradorDePartidas::getInstancia().crearPartida(
										CrearPartida(
												comando_a_pasar_provisorio));
						NotificarIdPartida nid(id_partida_creada);
						this->enviarMensaje(nid);
						break;
					}
					case comandos_logueo_posibles::solicitar_partidas_no_iniciadas: {
						ListaPartidas lpni(this->getId(),
								AdministradorDePartidas::getInstancia().listarPartidasNoIniciadas());
						this->enviarMensaje(lpni);
						break;
					}
					case comandos_logueo_posibles::solicitar_todas_las_partidas: {
						protocolo.enviarMensaje(
								AdministradorDePartidas::getInstancia().listarPartidas());
						break;
					}
					case comandos_logueo_posibles::unirse_a_partida: {
						AdministradorDePartidas::getInstancia().unirseAPartida(
								UnirseAPartida(comando_a_pasar_provisorio),
								*this);
						if (AdministradorDePartidas::getInstancia().clienteEstaEnAlgunaPartida(
								*this))
							if (estado_partida
									== estados_posibles_T::partida_no_iniciada)
								estado_partida =
										estados_posibles_T::esperando_iniciar_partida;
						break;
					}
					case comandos_logueo_posibles::solicitar_escenarios: {
						ListaEscenarios le(this->getId(),
								Atlas::getInstancia().listarEscenarios());
						this->enviarMensaje(le);
						break;
					}
					}
				} catch (const std::out_of_range& comando_invalido) {
					Notificacion notif(NOTIFICACION_AVISO, ID_JUGADOR_INVALIDO,
							"Comando inválido.");
					this->enviarMensaje(notif);
				} catch (std::exception & e) {
					Notificacion notif(NOTIFICACION_AVISO, ID_JUGADOR_INVALIDO,
							e.what());
					this->enviarMensaje(notif);
				}
			}
		} catch (std::exception & e) {
			std::cerr << e.what() << std::endl;
			apagar();
			AdministradorDePartidas::getInstancia().salirDePartida(*this);
		}
	}
}

void ManejadorDeCliente::manejarPartida() {
	while (activo) {
		try {
			std::string mensaje(protocolo.recibirMensaje());
			if (mensaje == SALIR) {
				apagar();
				AdministradorDePartidas::getInstancia().salirDePartida(*this);
			} else {
				if (estado_partida == estados_posibles_T::partida_en_curso)
					buzon->agregarMensaje(Mensaje(id_jugador, mensaje));
			}
		} catch (std::exception & e) {
			std::cerr << e.what() << std::endl;
			apagar();
			AdministradorDePartidas::getInstancia().salirDePartida(*this);
		}
	}
}

void ManejadorDeCliente::run() {
	manejarPartidaNoIniciada();
	manejarPartida();
}

void ManejadorDeCliente::enviarMensaje(const std::string& mensaje) {
	protocolo.enviarMensaje(mensaje);
}

void ManejadorDeCliente::finalizarPartida() {
	activo = false;
	estado_partida = estados_posibles_T::partida_finalizada;
}

void ManejadorDeCliente::apagar() {
	if (activo) {
		finalizarPartida();
		protocolo.cerrarConexion();
	}
}

unsigned int ManejadorDeCliente::getId() const {
	return id;
}

bool ManejadorDeCliente::isActivo() const {
	return activo;
}

ManejadorDeCliente::~ManejadorDeCliente() {
}

void ManejadorDeCliente::iniciarPartidaYNotificarIdJugador(
		Buzon<Mensaje> * buzon, int id_jugador) {
	this->buzon = buzon;
	NotificarIdJugador nid(id_jugador);
	this->id_jugador = nid.getIdJugador();
	this->enviarMensaje(nid);
	estado_partida = estados_posibles_T::partida_en_curso;
}

void ManejadorDeCliente::enviarMensaje(const Mensaje& mensaje) {
	this->enviarMensaje(mensaje.serializar());
}

/*
 * ProcesadorDeEntradas.cpp
 */

#include "ProcesadorDeEntradas.h"

#include <iostream>
#include <stdexcept>

#include "../comun/Codigos.h"
#include "../comun/Protocolo/ActualizarVida.h"
#include "../comun/Protocolo/Armas/Atacar.h"
#include "../comun/Protocolo/Armas/CargarArma.h"
#include "../comun/Protocolo/Armas/TeletransportarGusano.h"
#include "../comun/Protocolo/Balas/CrearBala.h"
#include "../comun/Protocolo/Balas/DestruirBala.h"
#include "../comun/Protocolo/Balas/ImpactarBala.h"
#include "../comun/Protocolo/Balas/MoverBala.h"
#include "../comun/Protocolo/ErroresYNotificaciones/ErrorParaTodos.h"
#include "../comun/Protocolo/ErroresYNotificaciones/Notificacion.h"
#include "../comun/Protocolo/Escenario/CrearGusano.h"
#include "../comun/Protocolo/Escenario/CrearViga.h"
#include "../comun/Protocolo/InformarViento.h"
#include "../comun/Protocolo/MovimientosGusanos/MoverGusano.h"
#include "../comun/Protocolo/MovimientosGusanos/VolarGusano.h"
#include "../comun/Protocolo/NotificarGanador.h"
#include "../comun/Protocolo/Protocolo.h"
#include "../comun/Protocolo/Turnos/FinalizarTurno.h"
#include "../comun/Protocolo/Turnos/IniciarTurno.h"
#include "../comun/Protocolo/Turnos/TiempoRestante.h"
#include "../comun/Protocolo/Visuales/DescargarArma.h"
#include "../comun/Protocolo/Visuales/DireccionarGusano.h"
#include "../comun/Protocolo/Visuales/MoverPunteria.h"

#include "../comun/Protocolo/NotificarIdJugador.h"
#include "../comun/Protocolo/NotificarIdPartida.h"

#include "../comun/Protocolo/Listas/ListaPartidas.h"
#include "../comun/Protocolo/Listas/ListaEscenarios.h"

ProcesadorDeEntradas::ProcesadorDeEntradas(SdlPartida & partida,
		SdlJuego & sdl_juego) :
		partida(partida), sdl_juego(sdl_juego) {
	inicializarComandosRespuestasLogueo();
	inicializarComandosEscenario();
	inicializarComandosPartida();
}

void ProcesadorDeEntradas::inicializarComandosEscenario() {
	this->comandos_escenario[CREAR_VIGA] = cmd_cargando_escenario::crear_viga;
	this->comandos_escenario[CREAR_GUSANO] =
			cmd_cargando_escenario::crear_gusano;
	this->comandos_escenario[FINALIZAR_ESCENARIO] =
			cmd_cargando_escenario::fin_escenario;
}

void ProcesadorDeEntradas::inicializarComandosRespuestasLogueo() {
	this->respuestas_logueo[NOTIFICAR_ID_PARTIDA] =
			respuestas_logueo_T::notificar_id_partida;
	this->respuestas_logueo[LISTA_PARTIDAS_NO_INICIADAS] =
			respuestas_logueo_T::lista_partidas_no_iniciadas;
	this->respuestas_logueo[LISTA_ESCENARIOS] =
			respuestas_logueo_T::lista_escenarios;
	this->respuestas_logueo[NOTIFICAR_ID_JUGADOR] =
				respuestas_logueo_T::notificar_id_jugador;
	this->respuestas_logueo[NOTIFICACION] =
				respuestas_logueo_T::notificacion_recibida;
}

void ProcesadorDeEntradas::inicializarComandosPartida() {
	this->comandos_partida[MOVER_GUSANO] = cmd_partida_en_juego::mover_gusano;

	this->comandos_partida[CARGAR_ARMA] = cmd_partida_en_juego::cargar_arma;
	this->comandos_partida[DESCARGAR_ARMA] =
			cmd_partida_en_juego::descargar_arma;
	this->comandos_partida[MOVER_PUNTERIA] =
			cmd_partida_en_juego::mover_punteria;

	this->comandos_partida[DIRECCIONAR_GUSANO] =
			cmd_partida_en_juego::direccionar_gusano;

	this->comandos_partida[ATACAR] = cmd_partida_en_juego::atacar;
	this->comandos_partida[ACTUALIZAR_VIDA] =
			cmd_partida_en_juego::actualizar_vida;

	this->comandos_partida[INICIAR_PARTIDA] =
			cmd_partida_en_juego::iniciar_partida;
	this->comandos_partida[FINALIZAR_PARTIDA] =
			cmd_partida_en_juego::finalizar_partida;

	this->comandos_partida[MENSAJE_DE_ERROR] = cmd_partida_en_juego::error;

	this->comandos_partida[TELETRANSPORTAR_GUSANO] =
			cmd_partida_en_juego::teletransportar_gusano;

	this->comandos_partida[CREAR_BALA] = cmd_partida_en_juego::crear_bala;
	this->comandos_partida[MOVER_BALA] = cmd_partida_en_juego::mover_bala;
	this->comandos_partida[DESTRUIR_BALA] = cmd_partida_en_juego::destruir_bala;
	this->comandos_partida[IMPACTAR_BALA] = cmd_partida_en_juego::impactar_bala;

	this->comandos_partida[VOLAR_GUSANO] = cmd_partida_en_juego::volar_gusano;

	this->comandos_partida[INICIAR_TURNO] = cmd_partida_en_juego::iniciar_turno;
	this->comandos_partida[FINALIZAR_TURNO] =
			cmd_partida_en_juego::finalizar_turno;

	this->comandos_partida[NOTIFICAR_GANADOR] =
			cmd_partida_en_juego::notificar_ganador;
	this->comandos_partida[NOTIFICACION] = cmd_partida_en_juego::notificacion;

	this->comandos_partida[TIEMPO_RESTANTE] =
			cmd_partida_en_juego::tiempo_restante;
	this->comandos_partida[INFORMAR_VIENTO] =
			cmd_partida_en_juego::informar_viento;
}

void ProcesadorDeEntradas::procesarComandoInvalido(const std::string& mensaje) {
	std::cerr << "Comando recibido del server inválido: " << mensaje
			<< std::endl;
}

void ProcesadorDeEntradas::procesarExcepcion(std::exception& e) {
	std::cerr << e.what() << std::endl;
}

void ProcesadorDeEntradas::procesarLogueo(const std::string mensaje,
		estados_posibles_partida & estado_partida,
		Destinatario * destinatario) {
	std::istringstream comando_a_parsear(mensaje);
	std::string sigla;
	sigla.clear();
	comando_a_parsear >> sigla;

	try {
		switch (respuestas_logueo.at(sigla)) {
		case respuestas_logueo_T::notificar_id_partida: {
			NotificarIdPartida nid(mensaje);
			sdl_juego.notificarIdPartida(nid.getIdPartida());
			break;
		}
		case respuestas_logueo_T::lista_partidas_no_iniciadas: {
			ListaPartidas lp(mensaje);
			sdl_juego.setPartidas(lp);
			break;
		}
		case respuestas_logueo_T::lista_escenarios: {
			ListaEscenarios le(mensaje);
			sdl_juego.setEscenarios(le);
			break;
		}
		case respuestas_logueo_T::notificar_id_jugador: {
			NotificarIdJugador nid(mensaje);
			destinatario->setIdJugador(nid.getIdJugador());
			estado_partida = estados_posibles_partida::cargando_escenario;
			break;
		}
		case respuestas_logueo_T::notificacion_recibida: {
			Notificacion notif(mensaje);
			if (notif.getTipoNotificacion() == NOTIFICACION_ERROR)
				sdl_juego.mostrarError(notif.getNotificacion());
			else
				sdl_juego.mostrarMje(notif.getNotificacion());
			break;
		}
		}
	} catch (const std::out_of_range& comando_invalido) {
		procesarComandoInvalido(mensaje);
	} catch (std::exception & e) {
		procesarExcepcion(e);
	}
}

void ProcesadorDeEntradas::procesarCargarEscenario(const std::string mensaje,
		estados_posibles_partida & estado_partida) {
	std::istringstream comando_a_parsear(mensaje);
	std::string sigla;
	sigla.clear();
	comando_a_parsear >> sigla;

	try {
		switch (this->comandos_escenario.at(sigla)) {
		case cmd_cargando_escenario::crear_viga: {
			CrearViga viga(mensaje);
			this->partida.crearViga(viga);
			break;
		}
		case cmd_cargando_escenario::crear_gusano: {
			CrearGusano gusano(mensaje);
			this->partida.crearGusano(gusano);
			break;
		}
		case cmd_cargando_escenario::fin_escenario: {
			estado_partida = en_curso;
			break;
		}
		}
	} catch (const std::out_of_range& comando_invalido) {
		procesarComandoInvalido(mensaje);
	} catch (std::exception & e) {
		procesarExcepcion(e);
	}
}

void ProcesadorDeEntradas::procesarPartidaEnJuego(const std::string mensaje,
		Destinatario * destinatario) {
	std::istringstream comando_a_parsear(mensaje);
	std::string sigla;
	sigla.clear();
	comando_a_parsear >> sigla;

	try {
		switch (this->comandos_partida.at(sigla)) {
		case cmd_partida_en_juego::mover_gusano: {
			MoverGusano mg(mensaje);
			partida.mover(mg);
			break;
		}
		case cmd_partida_en_juego::cargar_arma: {
			CargarArma ca(mensaje);
			partida.cargarArma(ca);
			break;
		}
		case cmd_partida_en_juego::iniciar_partida: {
			partida.mostrarMje("Inició la partida");
			break;
		}
		case cmd_partida_en_juego::mover_punteria: {
			MoverPunteria mp(mensaje);
			partida.moverPunteria(mp.getPunteria());
			break;
		}
		case cmd_partida_en_juego::descargar_arma: {
			DescargarArma da(mensaje);
			partida.descargarArma();
			break;
		}
		case cmd_partida_en_juego::direccionar_gusano: {
			DireccionarGusano dir(mensaje);
			partida.direccionar(dir.getDireccion());
			break;
		}
		case cmd_partida_en_juego::atacar: {
			Atacar at(mensaje);
			partida.atacar();
			break;
		}
		case cmd_partida_en_juego::crear_bala: {
			CrearBala cb(mensaje);
			partida.crearBala(cb);
			break;
		}
		case cmd_partida_en_juego::mover_bala: {
			MoverBala mb(mensaje);
			partida.moverBala(mb);
			break;
		}
		case cmd_partida_en_juego::impactar_bala: {
			ImpactarBala ib(mensaje);
			partida.impactarBala(ib);
			break;
		}
		case cmd_partida_en_juego::destruir_bala: {
			DestruirBala db(mensaje);
			partida.destruirBala(db);
			break;
		}
		case cmd_partida_en_juego::volar_gusano: {
			VolarGusano vg(mensaje);
			break;
		}
		case cmd_partida_en_juego::iniciar_turno: {
			IniciarTurno it(mensaje);
			destinatario->setIdJugadorActivo(it.getIdJugador());
			partida.iniciarTurno(it);
			break;
		}
		case cmd_partida_en_juego::finalizar_turno: {
			FinalizarTurno ft(mensaje);
			partida.finalizarTurno(ft);
			break;
		}
		case cmd_partida_en_juego::notificar_ganador: {
			NotificarGanador ng(mensaje);
			partida.mostrarGanador(ng);
			break;
		}
		case cmd_partida_en_juego::notificacion: {
			Notificacion notif(mensaje);
			if (notif.getTipoNotificacion() == NOTIFICACION_ERROR)
				partida.mostrarError(notif.getNotificacion());
			else
				partida.mostrarMje(notif.getNotificacion());
			break;
		}
		case cmd_partida_en_juego::tiempo_restante: {
			TiempoRestante tr(mensaje);
			partida.notificarTiempoRestante(tr);
			break;
		}
		case cmd_partida_en_juego::informar_viento: {
			InformarViento iv(mensaje);
			partida.informarViento(iv);
			break;
		}
		case cmd_partida_en_juego::actualizar_vida: {
			ActualizarVida av(mensaje);
			partida.actualizarVida(av);
			break;
		}
		case cmd_partida_en_juego::finalizar_partida: {
			partida.mostrarMje("Finalizó la partida");
			break;
		}
		case cmd_partida_en_juego::error: {
			ErrorParaTodos msj_error(mensaje);
			partida.mostrarError(msj_error.getMensajeDeError());
			break;
		}
		case cmd_partida_en_juego::teletransportar_gusano: {
			TeletransportarGusano tg(mensaje);
			partida.teletransportar(tg);
			break;
		}
		}
	} catch (const std::out_of_range& comando_invalido) {
		procesarComandoInvalido(mensaje);
	} catch (std::exception & e) {
		procesarExcepcion(e);
	}
}

ProcesadorDeEntradas::~ProcesadorDeEntradas() {
}

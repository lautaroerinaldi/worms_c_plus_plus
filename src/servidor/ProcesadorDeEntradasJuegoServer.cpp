/*
 * ProcesadorDeEntradasJuegoServer.cpp
 */

#include "ProcesadorDeEntradasJuegoServer.h"

#include <iostream>
#include <stdexcept>

#include "../comun/Protocolo/Protocolo.h"
#include "../comun/Protocolo/Solicitudes/SolicitarArma.h"
#include "../comun/Protocolo/Solicitudes/SolicitarAtacar.h"
#include "../comun/Protocolo/Solicitudes/SolicitarRetroceso.h"
#include "../comun/Protocolo/Solicitudes/SolicitarSaltar.h"
#include "../comun/Protocolo/Visuales/DescargarArma.h"
#include "../comun/Protocolo/Visuales/DireccionarGusano.h"
#include "../comun/Protocolo/Visuales/MoverPunteria.h"

ProcesadorDeEntradasJuegoServer::ProcesadorDeEntradasJuegoServer(
		Modelo & modelo, Buzon<Mensaje> & buzon_salida) :
		modelo(modelo), buzon_salida(buzon_salida) {
	this->inicializarComandosPartida();
}

void ProcesadorDeEntradasJuegoServer::inicializarComandosPartida() {
	comandos[SOLICITAR_MOVER] = solicitar_mover;
	comandos[SOLICITAR_SALTAR] = solicitar_saltar;
	comandos[SOLICITAR_RETROCESO] = solicitar_retroceso;
	comandos[SOLICITAR_ARMA] = solicitar_arma;
	comandos[SOLICITAR_ATACAR] = solicitar_atacar;
	comandos[MOVER_PUNTERIA] = mover_punteria_reenviar;
	comandos[DESCARGAR_ARMA] = descargar_arma_reenviar;
	comandos[DIRECCIONAR_GUSANO] = direccionar_reenviar;
}

void ProcesadorDeEntradasJuegoServer::procesarPartidaEnJuego(
		const std::string & mensaje) {
	std::istringstream comando_a_parsear(mensaje);
	std::string sigla("");
	comando_a_parsear >> sigla;

	try {
		switch (comandos.at(sigla)) {
		case solicitar_mover: {
			SolicitarMover sm(mensaje);
			modelo.aplicar(sm);
			break;
		}
		case solicitar_saltar: {
			SolicitarSaltar ss(mensaje);
			modelo.aplicar(ss);
			break;
		}
		case solicitar_retroceso: {
			SolicitarRetroceso sr(mensaje);
			modelo.aplicar(sr);
			break;
		}
		case solicitar_arma: {
			SolicitarArma sa(mensaje);
			modelo.aplicar(sa);
			break;
		}
		case solicitar_atacar: {
			SolicitarAtacar sataq(mensaje);
			modelo.aplicar(sataq);
			break;
		}
		case mover_punteria_reenviar: {
			MoverPunteria mp(mensaje);
			buzon_salida.agregarMensaje(mp);
			break;
		}
		case descargar_arma_reenviar: {
			DescargarArma da(mensaje);
			buzon_salida.agregarMensaje(da);
			break;
		}
		case direccionar_reenviar: {
			DireccionarGusano dir(mensaje);
			buzon_salida.agregarMensaje(DireccionarGusano(dir.getDireccion()));
			break;
		}
		}
	} catch (const std::out_of_range& comando_invalido) {
		std::cerr << "Comando Recibido inválido." << std::endl;
	} catch (std::exception & e) {
		std::cerr << e.what() << std::endl;
	}
}

ProcesadorDeEntradasJuegoServer::~ProcesadorDeEntradasJuegoServer() {
}

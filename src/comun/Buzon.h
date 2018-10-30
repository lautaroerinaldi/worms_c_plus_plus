/*
 * Buzon.h
 */

#ifndef SRC_COMUN_BUZON_H_
#define SRC_COMUN_BUZON_H_

#include <queue>

#include "Threads/Lock.h"
#include "Threads/Mutex.h"
#include "Utiles/Excepcion.h"

template<class T>

class Buzon {
	Mutex mutex;
	std::queue<T> mensajes;
public:
	Buzon() {
	}

	~Buzon() {
	}

	void agregarMensaje(const T & mensaje) {
		Lock lock(this->mutex);
		mensajes.push(mensaje);
	}

	T obtenerMensaje() throw (std::exception) {
		Lock lock(this->mutex);
		if (!mensajes.empty()) {
			T mensaje(mensajes.front());
			mensajes.pop();
			return mensaje;
		} else {
			throw Excepcion("No hay mensajes en el buzón.");
		}
	}

	bool hayMensajes() const {
		return (!mensajes.empty());
	}

	void vaciar() {
		Lock lock(this->mutex);
		while (!mensajes.empty())
			mensajes.pop();
	}

	// COPIAR Buzon
	Buzon(const Buzon& otro) = delete;
	Buzon& operator=(const Buzon& otro) = delete;

	// MOVER Buzon
	Buzon(Buzon&& otro) = delete;
	Buzon& operator=(Buzon&& otro) = delete;
};

#endif /* SRC_COMUN_BUZON_H_ */

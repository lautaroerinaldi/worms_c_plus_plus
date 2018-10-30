/**
 * Thread.h
 */

#ifndef COMUN_THREADS_THREAD_H_
#define COMUN_THREADS_THREAD_H_

#include <pthread.h>

class Thread {
private:
	pthread_t thread;
	static void *starter(void *data);

protected:
	/*
	 * Redefinir. Corresponde al bloque principal del hilo,
	 * y será ejecutado luego de inicializado el mismo.
	 */
	virtual void run() = 0;

public:
	/*
	 *
	 */
	explicit Thread();
	/*
	 * Llamar para inicializar el hilo. Una vez terminada la inicialización,
	 * se llama al método Run, el cuál debe ser definido por las clases
	 * herederas de Thread.
	 */
	void start();

	/*
	 * Llamar desde el hilo iniciador.
	 * Realiza el join con este hilo desde aquel del que se llama el método.
	 */
	void join();

	/*
	 * Libera los recursos asociados al hilo.
	 */
	virtual ~Thread();

	//COPIAR Threads
	Thread(const Thread& otro) = delete;
	Thread& operator=(const Thread& otro) = delete;

	// MOVER Threads
	Thread(Thread&& otro) = delete;
	Thread& operator=(Thread&& otro) = delete;
};

#endif

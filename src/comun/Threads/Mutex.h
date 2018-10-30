/**
 * Mutex.h
 */

#ifndef COMUN_THREADS_MUTEX_H_
#define COMUN_THREADS_MUTEX_H_

#include <pthread.h>

class Mutex {
	pthread_mutex_t mutex;

public:
	explicit Mutex();

	void lock();

	void unlock();

	// COPIAR Mutex
	Mutex(const Mutex& otro) = delete;
	Mutex& operator=(const Mutex& otro) = delete;

	//MOVER Mutex
	Mutex(Mutex&& otro) = delete;
	Mutex& operator=(Mutex&& otro) = delete;

	~Mutex();
};

#endif

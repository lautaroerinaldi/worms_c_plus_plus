/**
 * Lock.h
 */

#ifndef COMUN_THREADS_LOCK_H_
#define COMUN_THREADS_LOCK_H_

#include "Mutex.h"

class Lock {
private:
	Mutex &mutex;

public:
	explicit Lock(Mutex &mutex);

	//COPIAR Lock
	Lock(const Lock& otro) = delete;
	Lock& operator=(const Lock& otro) = delete;

	//MOVER Lock
	Lock(Lock&& otro) = delete;
	Lock& operator=(Lock&& otro) = delete;

	virtual ~Lock();
};

#endif

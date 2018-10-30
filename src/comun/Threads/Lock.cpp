/**
 * Lock.cpp
 */

#include "../../comun/Threads/Lock.h"

Lock::Lock(Mutex &mutex) :
		mutex(mutex) {
	mutex.lock();
}

Lock::~Lock() {
	mutex.unlock();
}

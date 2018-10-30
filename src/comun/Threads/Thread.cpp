/**
 * Thread.cpp
 */

#include "../../comun/Threads/Thread.h"

#include <utility>

Thread::Thread() :
		thread() {
}

void *Thread::starter(void *data) {
	Thread *hilo = (Thread *) data;
	hilo->run();
	return NULL;
}

void Thread::start() {
	pthread_create(&this->thread, NULL, Thread::starter, this);
}

void Thread::join() {
	pthread_join(this->thread, NULL);
}

Thread::~Thread() {
}

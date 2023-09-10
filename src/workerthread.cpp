#include "workerthread.h"
#include "mutexmanager.h"

WorkerThread::WorkerThread() {}

void WorkerThread::run()
{
    QMutex& mutex = MutexManager::getMutex();
    mutex.lock();
    int sharedVariable = 0;
    for (int i = 0; i < 10; ++i)
        ++sharedVariable;
    mutex.unlock();
    emit resultReady("Result from thread");
}


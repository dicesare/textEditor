#include "mutexmanager.h"

QMutex& MutexManager::getMutex() {
    static QMutex mutex;
    return mutex;
}

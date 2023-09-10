#ifndef MUTEXMANAGER_H
#define MUTEXMANAGER_H

#include <QMutex>

/**
 * @class MutexManager
 * @brief Singleton class responsible for mutex management.
 * 
 * The MutexManager class serves as a singleton that provides a QMutex instance for managing 
 * synchronization locks. This ensures a centralized control of mutex operations.
 */
class MutexManager {
public:
    /**
     * @brief Retrieve the mutex instance.
     * 
     * This static method returns a reference to the QMutex instance that is controlled by this class.
     * 
     * @return A reference to the managed QMutex instance.
     */
    static QMutex& getMutex();
};

#endif // MUTEXMANAGER_H

#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>
#include <QDebug>
#include "mutexmanager.h"

/**
 * @class WorkerThread
 * @brief A worker thread that performs background tasks.
 * 
 * The WorkerThread class inherits from QThread and overrides the run() method to execute 
 * background tasks in a separate thread. It utilizes mutex locks for thread synchronization.
 */
class WorkerThread : public QThread {
    Q_OBJECT  // Qt's macro for enabling signals and slots

public:
    /**
     * @brief Default constructor.
     * 
     * Initializes a new instance of the WorkerThread class.
     */
    WorkerThread();

    /**
     * @brief Overridden run method.
     * 
     * This method contains the code that will be executed when the thread is started.
     */
    void run() override;

signals:
    /**
     * @brief Signal emitted when the thread's work is completed.
     * 
     * This signal is emitted to notify that the thread has finished its work and 
     * to pass the result back to the main thread.
     * 
     * @param result The result of the work, as a QString.
     */
    void resultReady(const QString &result);
};

#endif // WORKERTHREAD_H

#include <QApplication>

#include "view/mainwindow.h"
#include "filemanagement/pathglobal.h"
#include "workerthread.h"

/**
 * @brief Main function of the program
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char *argv[])
{
    WorkerThread thread1, thread2;
    thread1.start();
    thread2.start();
    thread1.wait();
    thread2.wait();
    // Initialisez le chemin global dès le début
    PathGlobal::setGlobalPath(QDir::homePath() + "/Documents");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

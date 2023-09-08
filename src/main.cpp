#include "src/view/mainwindow.h"

#include <QApplication>

/**
 * @brief Main function of the program
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char *argv[])
{
    // Initialisez le chemin global dès le début
    PathGlobal::setGlobalPath(QDir::homePath() + "/Documents");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

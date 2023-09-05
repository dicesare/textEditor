#include "src/View/mainwindow.h"

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
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

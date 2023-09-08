#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <ui_mainwindow.h>

#include "../controller/controllereditor.h"
#include "../filemanagement/pathglobal.h"

#include "tabwidget.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString getCurrentDirectory() const;

private slots:
    void openFile();
    void saveFile();

private:
    Ui::MainWindow *ui;
    ControllerEditor m_controllerEditor;
    TabWidget *m_tabWidget;
    QString mCurrentDirectory = PathGlobal::getGlobalPath();
};
#endif // MAINWINDOW_H

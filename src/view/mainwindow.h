#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QDebug>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QMainWindow>
#include "../controller/controllereditor.h"
#include "../filemanagement/pathglobal.h"

#include "tabwidgeteditor.h"


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
    bool m_initialTabWidget;
    QString mCurrentDirectory = PathGlobal::getGlobalPath();
};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include "ui_mainwindow.h"

#include "../viewmodel/editorviewmodel.h"
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

private slots:
    void openFile();
    void saveFile();

private:
    Ui::MainWindow *ui;
    EditorViewModel m_editorViewModel;
};
#endif // MAINWINDOW_H

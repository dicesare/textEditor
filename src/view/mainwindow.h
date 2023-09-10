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
#include <QSettings>
#include <QListWidget>
#include "../controller/controllereditor.h"
#include "../filemanagement/pathglobal.h"

#include "tabwidgeteditor.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString getCurrentDirectory() const;

public slots:
    void updateCursorPosition(CustomTextEdit *editor);
    void openSelectedFile(QListWidgetItem* item);

private slots:
    void openFile();
    void saveFile();
    void pushButtonFind_clicked();
    void pushButtonPrevious_clicked();
    void pushButtonNext_clicked();
    void pushButtonReplace_clicked();
    void loadRecentFiles();
    void openRecentFile(const QString &filePath);
    void openSelectedFileFromButton();

private:
    Ui::MainWindow *ui;
    ControllerEditor m_controllerEditor;
    bool m_initialTabWidget;
    QString mCurrentDirectory = PathGlobal::getGlobalPath();
    QTextCursor m_lastFoundCursor;
    QStringList m_recentFiles;
    static const int MaxRecentFiles = 10;
    QSettings m_settings;
};
#endif // MAINWINDOW_H

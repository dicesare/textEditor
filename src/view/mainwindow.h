#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFile>
#include <QDebug>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QSettings>
#include <QListWidget>
#include "../controller/controllereditor.h"
#include "../filemanagement/pathglobal.h"
#include "ui_mainwindow.h"

#include "tabwidgeteditor.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

/**
 * @class MainWindow
 * @brief Represents the main application window.
 * 
 * This class is responsible for the initialization and management of the main application window.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString getCurrentDirectory() const;

public slots:

    /**
     * @brief Responds to text modification events.
     * 
     * @param modified Whether the text is modified or not.
     */
    void updateCursorPosition(CustomTextEdit *editor);

    /**
     * @brief Responds to text modification events.
     * 
     * @param modified Whether the text is modified or not.
     */
    void openSelectedFile(QListWidgetItem* item);

private slots:
    void openFile();
    void saveFile();
    void onSaveAsTriggered();
    void pushButtonFind_clicked();
    void pushButtonPrevious_clicked();
    void pushButtonNext_clicked();
    void pushButtonReplace_clicked();
    void loadRecentFiles();
    void openRecentFile(const QString &filePath);
    void openSelectedFileFromButton();

private:
    Ui::MainWindow *ui; ///< The user interface design for this MainWindow.
    ControllerEditor m_controllerEditor; ///< Controller to handle editor-specific functionalities.
    bool m_initialTabWidget; ///< Whether or not the tab widget has been initialized.
    QString mCurrentDirectory = PathGlobal::getGlobalPath(); ///< The current directory.
    QTextCursor m_lastFoundCursor; ///< Last found cursor for find functionality.
    QStringList m_recentFiles; ///< List of recently opened files.
    static const int MaxRecentFiles = 10; ///< Maximum number of recent files.
    QSettings m_settings; ///< Settings for the application.
    bool m_shouldShowSaveDialog = false; ///< Flag for displaying the save dialog.
    bool m_actionSaveAsTriggered = false; ///< Flag for triggering the "Save As" action.
};

#endif // MAINWINDOW_H

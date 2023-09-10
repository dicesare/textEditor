#ifndef TABWIDGETEDITOR_H
#define TABWIDGETEDITOR_H

#include <QTabWidget>
#include <QTextEdit>
#include <QMessageBox>
#include <QFileDialog>
#include <QVector>

#include "../controller/controllereditor.h"
#include "../filemanagement/pathglobal.h"
#include "customtextedit.h"

/**
 * @class TabWidgetEditor
 * @brief A class that manages the tab-based text editor interface.
 *
 * This class inherits from QTabWidget and controls the tabbed interface where each
 * tab represents an open text file. 
 */
class TabWidgetEditor : public QTabWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor that initializes the tab widget.
     * 
     * @param parent Parent widget.
     */
    explicit TabWidgetEditor(QWidget *parent = nullptr);

    /**
     * @brief Adds a new tab and populate it with given content and filepath.
     * 
     * @param content Content to fill in the new tab.
     * @param filePath Filepath to associate with the new tab.
     */
    void addTabWithContent(const QString &content, const QString &filePath);

    /**
     * @brief Set the modified state for a tab at given index.
     * 
     * @param index Index of the tab.
     * @param modified Whether the tab is modified or not.
     */
    void setTabModified(int index, bool modified);

    /**
     * @brief Responds to text modification events.
     * 
     * @param modified Whether the text is modified or not.
     */
    void handleTextModified(bool modified);

    /**
     * @brief Sets the modified state for the current QTextEdit.
     * 
     * @param modified Whether the text is modified or not.
     */
    void setCurrentTextEditModified(bool modified);

public slots:
    /**
     * @brief Close the tab at the given index.
     * 
     * @param index Index of the tab.
     */
    void closeTab(int index);

signals:
    /**
     * @brief Signal emitted when the cursor's position changes in the editor.
     * 
     * @param editor Pointer to the CustomTextEdit where the event occurred.
     */
    void cursorPositionChangedInEditor(CustomTextEdit *editor);

    /**
     * @brief Signal emitted when a file gets modified.
     * 
     * @param modified Whether the file is modified or not.
     */
    void fileModified(bool modified);

private:
    ControllerEditor m_controllerEditor; ///< Controller for the editor logic.
    QVector<bool> m_modifiedTabs; ///< Tracks the modified state for each tab.
    CustomTextEdit *m_currentTextEdit; ///< Pointer to the currently active QTextEdit.
    QString mCurrentDirectory = PathGlobal::getGlobalPath(); ///< Current working directory.
};

#endif // TABWIDGETEDITOR_H

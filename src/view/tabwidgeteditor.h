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


class TabWidgetEditor : public QTabWidget
{
    Q_OBJECT

public:
    explicit TabWidgetEditor(QWidget *parent = nullptr);
    void addTabWithContent(const QString &content, const QString &filePath);
    void setTabModified(int index, bool modified);
    void handleTextModified(bool modified);
    void setCurrentTextEditModified(bool modified);

public slots:
    void closeTab(int index);

signals:
    void cursorPositionChangedInEditor(CustomTextEdit *editor);
    void fileModified (bool modified);

private:
    ControllerEditor m_controllerEditor;
    QVector<bool> m_modifiedTabs; // Utilisez QVector<bool> pour stocker l'état de chaque onglet
    CustomTextEdit *m_currentTextEdit;
    QString mCurrentDirectory = PathGlobal::getGlobalPath();
};

#endif // TABWIDGETEDITOR_H

#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QTabWidget>
#include <QTextEdit>
#include <QMessageBox>
#include <QFileDialog>
#include <QVector>

#include "../controller/controllereditor.h"
#include "../filemanagement/pathglobal.h"
#include "customtextedit.h"



class TabWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit TabWidget(QWidget *parent = nullptr);
    void addTabWithContent(const QString &content, const QString &filePath);
    void setTabModified(int index, bool modified);
    void handleTextModified(bool modified);

public slots:
    void closeTab(int index);

signals:
    void fileModified (bool modified);

private:
    ControllerEditor m_controllerEditor;
    QVector<bool> m_modifiedTabs; // Utilisez QVector<bool> pour stocker l'état de chaque onglet
    CustomTextEdit *m_currentTextEdit;
    QString mCurrentDirectory = PathGlobal::getGlobalPath();
};


#endif // TABWIDGET_H

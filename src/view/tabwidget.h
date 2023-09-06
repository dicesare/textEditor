#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QTabWidget>
#include <QTextEdit>
#include <QMessageBox>
#include <QFileDialog>
#include <QVector>

#include "../viewmodel/editorviewmodel.h"



class TabWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit TabWidget(QWidget *parent = nullptr);
    void addTabWithContent(const QString &content, const QString &filePath);
    void setTabModified(int index, bool modified);

private slots:
    void closeTab(int index);

private:
    EditorViewModel m_editorViewModel;
    QVector<bool> m_modifiedTabs; // Utilisez QVector<bool> pour stocker l'état de chaque onglet

};


#endif // TABWIDGET_H

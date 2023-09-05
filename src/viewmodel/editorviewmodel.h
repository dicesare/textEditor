#ifndef EDITORVIEWMODEL_H
#define EDITORVIEWMODEL_H

#include <QObject>
#include "../model/filemanager.h"

class EditorViewModel : public QObject
{
    Q_OBJECT
public:
    explicit EditorViewModel(QObject *parent = nullptr);

    Q_INVOKABLE bool openFile(const QString &filePath);

signals:
    void fileContentChanged(const QString &content); // Déclarer le signal

private:
    FileManager m_fileManager;
};

#endif // EDITORVIEWMODEL_H

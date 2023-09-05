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
    Q_INVOKABLE bool saveFile(const QString &filePath);
    QString getFileContent() const;
    void setFileContent(const QString &content);


signals:
    void fileContentChanged(const QString &content); // Déclarer le signal

private:
    FileManager m_fileManager;
    QString m_fileContent; // Variable pour stocker le contenu du fichier
};

#endif // EDITORVIEWMODEL_H

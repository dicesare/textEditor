#ifndef CONTROLLEREDITOR_H
#define CONTROLLEREDITOR_H


#include <QObject>
#include "../filemanagement/filemanager.h"

class ControllerEditor : public QObject
{
    Q_OBJECT
public:
    explicit ControllerEditor(QObject *parent = nullptr);

    QString getFileContent() const;
    void setFileContent(const QString &content);
    
public slots:
    Q_INVOKABLE bool openFile(const QString &filePath);
    Q_INVOKABLE bool saveFile(const QString &filePath, const QString &content);

signals:
    void fileContentChanged(const QString &content); // Déclarer le signal

private:
    FileManager m_fileManager;
    QString m_fileContent; // Variable pour stocker le contenu du fichier
};

#endif // CONTROLLEREDITOR_H

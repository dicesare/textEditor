#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QFile>
#include <QTextStream>
#include <QString>

class FileManager
{
public:
    explicit FileManager();
    bool readFile(const QString &filePath, QString &content);
    bool writeFile(const QString &filePath, QString &content);
};

#endif // FILEMANAGER_H

#include "filemanager.h"


FileManager::FileManager() {}

bool FileManager::readFile(const QString &filePath, QString &content)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&file);
    content = in.readAll();
    file.close();

    return true;
}

bool FileManager::writeFile(const QString &filePath, QString &content)
{
    QFile file(filePath);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    QTextStream out(&file);
    out << content;
    file.close();
    return true;
}

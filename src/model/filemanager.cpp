#include "filemanager.h"


FileManager::FileManager(QObject *parent) : QObject(parent) {}

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
#include "editorviewmodel.h"

EditorViewModel::EditorViewModel(QObject *parent) : QObject(parent) {}

QString EditorViewModel::getFileContent() const
{
    return m_fileContent;
}

void EditorViewModel::setFileContent(const QString &content)
{
    m_fileContent = content;
}

bool EditorViewModel::openFile(const QString &filePath)
{
    if (m_fileManager.readFile(filePath, m_fileContent))
    {
        emit fileContentChanged(m_fileContent); // Émettre le signal
        return true;
    }
    return false;
}

bool EditorViewModel::saveFile(const QString &filePath, const QString &content)
{
    QFile file(filePath);
    qDebug() << filePath;
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Error opening file for writing:" << file.errorString();
        return false;
    }

    QTextStream out(&file);
    out << content;
    file.close();

    return true;
}

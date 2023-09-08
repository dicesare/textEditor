#include "controllereditor.h"

ControllerEditor::ControllerEditor(QObject *parent) : QObject(parent) {}

QString ControllerEditor::getFileContent() const
{
    return m_fileContent;
}

void ControllerEditor::setFileContent(const QString &content)
{
    m_fileContent = content;
}

bool ControllerEditor::openFile(const QString &filePath)
{
    if (m_fileManager.readFile(filePath, m_fileContent))
    {
        emit fileContentChanged(m_fileContent); // Émettre le signal
        return true;
    }
    return false;
}

bool ControllerEditor::saveFile(const QString &filePath, const QString &content)
{
    QFile file(filePath);
    file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
    QTextStream out(&file);
    out << content;
    file.close();
    return true;
}
#include "controllereditor.h"

ControllerEditor::ControllerEditor(QObject *parent) : QObject(parent) {}

QString ControllerEditor::getFileContent() const
{
    return m_fileContent;
}

void ControllerEditor::setFileContent(const QString &content)
{
    m_fileContent = content;
    emit fileContentChanged(m_fileContent); // Emit the signal
}

bool ControllerEditor::openFile(const QString &filePath)
{
    QString content;
    if (m_fileManager.readFile(filePath, content))
    {
        setFileContent(content); // This will emit fileContentChanged
        return true;
    }
    qDebug() << "Failed to read file: " << filePath; // Diagnostic
    return false;
}

bool ControllerEditor::saveFile(const QString &filePath, const QString &content)
{
    if (m_fileManager.writeFile(filePath, content))
    {
        setFileContent(content); // This will emit fileContentChanged
        return true;
    }
    qDebug() << "Failed to write file: " << filePath; // Diagnostic
    return false;
}

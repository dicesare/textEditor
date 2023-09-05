#include "editorviewmodel.h"

EditorViewModel::EditorViewModel(QObject *parent) : QObject(parent) {}

QString EditorViewModel::getFileContent() const
{
    return m_fileContent;
}

bool EditorViewModel::openFile(const QString &filePath)
{
    if (m_fileManager.readFile(filePath, m_fileContent))
        emit fileContentChanged(m_fileContent); // Émettre le signal
        return true;


    return false;
}

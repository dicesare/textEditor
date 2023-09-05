#include "editorviewmodel.h"

EditorViewModel::EditorViewModel(QObject *parent) : QObject(parent) {}

bool EditorViewModel::openFile(const QString &filePath)
{
    QString content;
    if (!m_fileManager.readFile(filePath, content))
        return false;

    emit fileContentChanged(content); // Émettre le signal

    return true;
}

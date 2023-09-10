#ifndef CONTROLLEREDITOR_H
#define CONTROLLEREDITOR_H

#include <QObject>
#include "../filemanagement/filemanager.h"

/**
 * @class ControllerEditor
 * @brief A class that manages the text editor.
 * 
 * This class is responsible for managing the text editor. It is used to open and save files.
 */
class ControllerEditor : public QObject
{
    Q_OBJECT
public:

    /**
     * @brief Default constructor.
     * 
     * Initializes a new instance of the ControllerEditor class.
     * 
     * @param parent Parent object.
     */
    explicit ControllerEditor(QObject *parent = nullptr);

    /**
     * @brief Retrieve the file content.
     * 
     * This method returns the content of the file that is currently opened.
     * 
     * @return The content of the file that is currently opened.
     */
    QString getFileContent() const;

    /**
     * @brief Set the file content.
     * 
     * This method sets the content of the file that is currently opened.
     * 
     * @param content The content of the file that is currently opened.
     */
    void setFileContent(const QString &content);
    
public slots:

    /**
     * @brief Open a file.
     * 
     * This method opens a file and returns its content.
     * 
     * @param filePath The path to the file to open.
     * @return True if the file was opened successfully, false otherwise.
     */
    Q_INVOKABLE bool openFile(const QString &filePath);

    /**
     * @brief Save a file.
     * 
     * This method saves a file.
     * 
     * @param filePath The path to the file to save.
     * @param content The content to save.
     * @return True if the file was saved successfully, false otherwise.
     */
    Q_INVOKABLE bool saveFile(const QString &filePath, const QString &content);

signals:
    
    /**
     * @brief Signal emitted when the file content has changed.
     * 
     * @param content The new content of the file.
     */
    void fileContentChanged(const QString &content);

private:
    FileManager m_fileManager;  ///< The file manager. 
    QString m_fileContent; ///< The content of the file that is currently opened.
};

#endif // CONTROLLEREDITOR_H

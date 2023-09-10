#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QFile>
#include <QTextStream>
#include <QString>
#include <iostream>
#include <QDebug>

/**
 * @class FileManager
 * @brief Class responsible for file management.
 * 
 * FileManager class is used for managing files. It allows reading and writing to a file.
 */
class FileManager
{
public:
    /**
     * @brief Default constructor.
     * 
     * Initializes a new instance of the FileManager class.
     */
    explicit FileManager();

    /**
     * @brief Reads a file.
     * 
     * This method reads the content of a file and stores it in a string.
     * 
     * @param filePath The path of the file to read.
     * @param content The string where the file content will be stored.
     * @return true If reading succeeds.
     * @return false If reading fails.
     */
    bool readFile(const QString &filePath, QString &content);

    /**
     * @brief Writes to a file.
     * 
     * This method writes the content of a string to a file.
     * 
     * @param filePath The path of the file to write to.
     * @param content The string to write to the file.
     * @return true If writing succeeds.
     * @return false If writing fails.
     */
    bool writeFile(const QString &filePath, const QString &content);
};

#endif // FILEMANAGER_H

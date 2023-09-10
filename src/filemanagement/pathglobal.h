#ifndef PATHGLOBAL_H
#define PATHGLOBAL_H

#include <QString>
#include <QDir>

/**
 * @class PathGlobal
 * @brief Static class to manage the global path
 * 
 * The PathGlobal class is used to manage the global path of the application. It is designed to be static 
 * so that it can be accessed from any part of the application.
 */
class PathGlobal
{
public:

    /**
     * @brief Retrieve the global path.
     * 
     * @return QString representing the global path.
     */
    static QString getGlobalPath();
    
    /**
     * @brief Set the global path.
     * 
     * @param path The new global path as a QString.
     */
    static void setGlobalPath(const QString &path);

private:
    static QString m_globalPath; ///< Global path storage
};

#endif // PATHGLOBAL_H

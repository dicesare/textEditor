// pathglobal.h
#ifndef PATHGLOBAL_H
#define PATHGLOBAL_H

#include <QString>
#include <QDir>


class PathGlobal
{
public:
    // Méthode pour obtenir le chemin global
    static QString getGlobalPath();

    // Méthode pour définir le chemin global
    static void setGlobalPath(const QString &path);

private:
    // La variable statique qui stocke le chemin global
    static QString m_globalPath;
};

#endif // PATHGLOBAL_H

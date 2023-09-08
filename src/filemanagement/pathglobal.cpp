// pathglobal.cpp
#include "pathglobal.h"

// Initialiser la variable statique
QString PathGlobal::m_globalPath = QDir::homePath() + "/Documents";

QString PathGlobal::getGlobalPath()
{
    return m_globalPath;
}

void PathGlobal::setGlobalPath(const QString &path)
{
    m_globalPath = path;
}

#include <scenematica/level.h>

namespace Scenematica {

Level::Level()
{
}

Level::Level(const std::string& levelName)
    : m_LevelName(levelName)
{
}

Level::Level(const std::string& levelName, const std::string& path)
    : m_LevelName(levelName)
    , m_LevelPath(path)
{
}

}

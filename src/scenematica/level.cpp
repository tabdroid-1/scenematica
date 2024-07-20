#include <scenematica/level.h>

namespace Scenematica {

Level::Level()
    : m_ClearColor({ 0.5f, 0.5f, 0.5f, 1.0f })
{
}

Level::Level(const std::string& levelName)
    : m_LevelName(levelName)
    , m_ClearColor({ 0.5f, 0.5f, 0.5f, 1.0f })
{
}

Level::Level(const std::string& levelName, const std::string& path)
    : m_LevelName(levelName)
    , m_LevelPath(path)
    , m_ClearColor({ 0.5f, 0.5f, 0.5f, 1.0f })
{
}

Level::~Level()
{
}

Element& Level::CreateElement(const std::string& name)
{
    Element element(name);

    m_ElementList[element.GetUUID()] = element;

    return m_ElementList[element.GetUUID()];
}

Element& Level::GetElement(UUID elementID)
{
    auto it = m_ElementList.find(elementID);
    if (it == m_ElementList.end()) {
        throw std::runtime_error("Element not found");
    }

    return it->second;
}

}

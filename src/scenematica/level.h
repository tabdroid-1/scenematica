#pragma once

#include <scenematica/elements.h>
#include <scenematica/types.h>

namespace Scenematica {

class Level {
public:
    Level();
    Level(const std::string& levelName);
    Level(const std::string& levelName, const std::string& path);
    ~Level();

    const std::string& GetLevelName() { return m_LevelName; }
    const std::string& GetLevelPath() { return m_LevelPath; }
    const Color& GetLevelClearColor() { return m_ClearColor; }

    void SetLevelName(const std::string& name) { m_LevelName = name; }
    void SetLevelPath(const std::string& path) { m_LevelPath = path; }
    void SetLevelClearColor(const Color& color) { m_ClearColor = color; }

    Element& CreateElement(const std::string& name);
    Element& GetElement(UUID elementID);

    const std::unordered_map<UUID, Element>& GetElementMap() { return m_ElementList; }

private:
    std::string m_LevelName;
    std::string m_LevelPath;
    Color m_ClearColor;
    std::unordered_map<UUID, Element> m_ElementList;
};

}

#pragma once

#include <scenematica/group.h>
#include <scenematica/types.h>

namespace Scenematica {

class Level {
public:
    Level();
    Level(const std::string& levelName);
    Level(const std::string& levelName, const std::string& path);

    const std::string& GetLevelName() { return m_LevelName; }
    const std::string& GetLevelPath() { return m_LevelPath; }
    const Color& GetLevelClearColor() { return m_ClearColor; }

    void SetLevelName(const std::string& name) { m_LevelName = name; }
    void SetLevelPath(const std::string& path) { m_LevelPath = path; }
    void SetLevelClearColor(const Color& color) { m_ClearColor = color; }

    ElementGroup& GetRootElementGroup() { return m_RootElementGroup; }

private:
    std::string m_LevelName;
    std::string m_LevelPath;
    Color m_ClearColor;
    ElementGroup m_RootElementGroup;
};

}

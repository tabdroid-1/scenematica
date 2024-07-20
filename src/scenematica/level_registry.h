#pragma once

#include <smpch.h>

namespace Scenematica {

class Level;

class LevelRegistry {
public:
    LevelRegistry();
    LevelRegistry(const std::string& path);
    LevelRegistry(const std::string& name, const std::string& version);

    auto& GetRegistryName() { return m_Name; }
    auto& GetLevelMap() { return m_LevelMap; }
    const auto& GetRegistryVersion() { return m_ScenematicaVersion; }

    static void SerializeToJson(const LevelRegistry& levelRegistry, const std::string& path);
    static LevelRegistry DeserializeFromJson(const std::string& path);

private:
    std::string m_Name;
    std::string m_ScenematicaVersion;
    std::unordered_map<std::string, std::shared_ptr<Level>> m_LevelMap;
};

}

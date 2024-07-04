#include <scenematica/level_registry.h>
#include <scenematica/version.h>
#include <json/json.hpp>

namespace Scenematica {

LevelRegistry::LevelRegistry()
    : m_Name("levelRegistry")
    , m_ScenematicaVersion(std::string(API_VERSION_STRING))

{
}

LevelRegistry::LevelRegistry(const std::string& name, const std::string& version)
    : m_Name(name)
    , m_ScenematicaVersion(version)

{
}

LevelRegistry::LevelRegistry(const std::string& path)
{
    auto levreg = DeserializeFromJson(path);
    m_Name = levreg.m_Name;
    m_ScenematicaVersion = levreg.m_ScenematicaVersion;
}

void LevelRegistry::SerializeToJson(const LevelRegistry& levelRegistry, const std::string& path)
{
    nlohmann::json data;

    data["Name"] = levelRegistry.m_Name;
    data["Version"] = levelRegistry.m_ScenematicaVersion;

    // for (const auto& grade : m_Grades) {
    //     m_Data["Students"][std::to_string(grade.studentNumber)]["Subjects"][grade.subject]["Grade"] = grade.grade;
    //
    //     m_Data["Students"][std::to_string(grade.studentNumber)]["Name"] = grade.firstName;
    //     m_Data["Students"][std::to_string(grade.studentNumber)]["Surname"] = grade.surname;
    // }
    //
    // for (const auto& average : m_Averages) {
    //
    //     m_Data["Students"][std::to_string(average.studentNumber)]["Average"] = average.averageGrade;
    // }

    std::ofstream output(path);
    output << std::setw(4) << data << std::endl;
}

LevelRegistry LevelRegistry::DeserializeFromJson(const std::string& path)
{
    nlohmann::json j;
    std::ifstream input(path);
    input >> j;

    LevelRegistry levelRegistry = LevelRegistry(j["Name"], j["Version"]);

    return levelRegistry;
}

}

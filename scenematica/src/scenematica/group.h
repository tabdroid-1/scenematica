#pragma once

#include <scenematica/elements.h>

namespace Scenematica {

class ElementGroup {
private:
    std::unordered_map<std::string, std::shared_ptr<Element>> m_LevelMap;
};

}

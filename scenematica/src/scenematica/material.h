#pragma once

#include <scenematica/asset_meta.h>

namespace Scenematica {

class Material {
private:
    std::unordered_map<std::string, Asset> m_MapList;
};

}

#pragma once

#include <smpch.h>

namespace Scenematica {

class Asset {
public:
    Asset(const std::string& path);
    Asset(const std::vector<uint8_t>& data);
    Asset(const std::string& path, const std::vector<uint8_t>& data);

private:
    // Asset can hold data and path.
    // This can be used to carry asset with level registrys it self and
    // m_Path can be used to asset overriding for modding and such.
    std::string m_Path;
    std::vector<uint8_t> m_Data;
};

class AssetMeta {
public:
    AssetMeta();

private:
    //                 Name         Asset
    std::unordered_map<std::string, Asset> m_AssetMap;
};

}

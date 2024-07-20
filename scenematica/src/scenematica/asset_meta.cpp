#include <scenematica/asset_meta.h>

namespace Scenematica {

Asset::Asset(const std::string& path)
    : m_Path(path)
{
}

Asset::Asset(const std::vector<uint8_t>& data)
    : m_Data(data)
{
}

Asset::Asset(const std::string& path, const std::vector<uint8_t>& data)
    : m_Path(path)
    , m_Data(data)
{
}

AssetMeta::AssetMeta()
{
}

}

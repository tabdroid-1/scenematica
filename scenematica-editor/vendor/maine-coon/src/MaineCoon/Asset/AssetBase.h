#pragma once

#include <MaineCoon/Asset/AssetType.h>
#include <MaineCoon/Foundation/Types.h>

namespace MaineCoon {

class AssetBase {
public:
    AssetHandle Handle;
    AssetType Type;

    virtual void Destroy() = 0;
    bool Valid() { return Handle.Valid(); }
};

}

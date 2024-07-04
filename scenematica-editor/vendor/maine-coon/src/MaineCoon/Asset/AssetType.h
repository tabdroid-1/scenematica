#pragma once

namespace MaineCoon {

enum class AssetType : uint8_t {
    AUDIO_SRC,
    IMAGE_SRC,
    FONT_SRC,
    MAINECOON_FONT,
    MAINECOON_IMAGE,
    UNKNOWN
};

inline static const std::unordered_map<std::string, AssetType> g_AssetTypesExtensionMap = {
    { ".ttf", AssetType::FONT_SRC },

    { ".png", AssetType::IMAGE_SRC },
    { ".jpg", AssetType::IMAGE_SRC },
    { ".jpeg", AssetType::IMAGE_SRC },
    { ".tga", AssetType::IMAGE_SRC },

    { ".mp3", AssetType::AUDIO_SRC },
    { ".wav", AssetType::AUDIO_SRC },

};

inline AssetType FileExtensionToAssetType(std::string_view extension)
{
    if (g_AssetTypesExtensionMap.find(extension.data()) != g_AssetTypesExtensionMap.end())
        return g_AssetTypesExtensionMap.at(extension.data());

    return AssetType::UNKNOWN;
}

}

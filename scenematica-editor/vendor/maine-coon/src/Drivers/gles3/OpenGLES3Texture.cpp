#include "Drivers/gles3/OpenGLES3Texture.h"
#include "Drivers/gles3/GLES3.h"
#include "SDL2/include/SDL_surface.h"
#include "mcpch.h"
#include <MaineCoon/Debug/Instrumentor.h>
#include <glad/gles3.h>

#include <stb_image.h>

namespace MaineCoon {

namespace Utils {

    static GLenum MaineCoonImageFormatToGLDataFormat(ImageFormat format)
    {
        switch (format) {
        case ImageFormat::RGB8:
            return GL_RGB;
        case ImageFormat::RGBA8:
            return GL_RGBA;
        }

        MC_CORE_ASSERT(false);
        return 0;
    }

    static GLenum MaineCoonImageFormatToGLInternalFormat(ImageFormat format)
    {
        switch (format) {
        case ImageFormat::RGB8:
            return GL_RGB8;
        case ImageFormat::RGBA8:
            return GL_RGBA8;
        }

        MC_CORE_ASSERT(false);
        return 0;
    }
}

OpenGLES3Texture::OpenGLES3Texture(const TextureSpecification& specification, AssetHandle handle, Buffer data)
    : Texture(0)
    , m_Specification(specification)
    , m_Width(m_Specification.Width)
    , m_Height(m_Specification.Height)
{
    // MC_PROFILE_FUNCTION();

    Handle = handle;
    m_InternalFormat = Utils::MaineCoonImageFormatToGLInternalFormat(m_Specification.Format);
    m_DataFormat = Utils::MaineCoonImageFormatToGLDataFormat(m_Specification.Format);

    GLES3::GL()->PixelStorei(GL_UNPACK_ALIGNMENT, m_Specification.UnpackAlignment);

    GLES3::GL()->GenTextures(1, &m_RendererID);
    GLES3::GL()->BindTexture(GL_TEXTURE_2D, m_RendererID);

    GLES3::GL()->TexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    if (m_Specification.GenerateMips) {

        GLES3::GL()->GenerateMipmap(GL_TEXTURE_2D);

        GLES3::GL()->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        GLES3::GL()->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        GLES3::GL()->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        GLES3::GL()->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    } else {
        GLES3::GL()->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        GLES3::GL()->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        GLES3::GL()->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        GLES3::GL()->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    if (data)
        SetData(data);
}

OpenGLES3Texture::~OpenGLES3Texture()
{
    Destroy();
}

void OpenGLES3Texture::SetData(Buffer data)
{
    // MC_PROFILE_FUNCTION();

    uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;
    MC_CORE_ASSERT_TAGGED(data.Size == m_Width * m_Height * bpp, "Data must be the entire texture!");

    GLES3::GL()->BindTexture(GL_TEXTURE_2D, m_RendererID);
    GLES3::GL()->TexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data.Data);
}

void OpenGLES3Texture::SetSubData(void* data, uint32_t width, uint32_t height)
{
    // MC_PROFILE_FUNCTION();

    GLES3::GL()->BindTexture(GL_TEXTURE_2D, m_RendererID);
    GLES3::GL()->TexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, m_DataFormat, GL_UNSIGNED_BYTE, data);
}

void OpenGLES3Texture::Bind(uint32_t slot) const
{
    // MC_PROFILE_FUNCTION();

    GLES3::GL()->ActiveTexture(GL_TEXTURE0 + slot);
    GLES3::GL()->BindTexture(GL_TEXTURE_2D, m_RendererID);
}

void OpenGLES3Texture::Destroy()
{
    MC_PROFILE_SCOPE_NAME("(Textures) Delete");

    GLES3::GL()->DeleteTextures(1, &m_RendererID);
}
}

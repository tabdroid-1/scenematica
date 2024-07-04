#include "Drivers/gl33/OpenGL33Texture.h"
#include "Drivers/gl33/GL33.h"
#include "mcpch.h"
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
        case ImageFormat::RGBA32_UNORM:
            return GL_RGB32UI;
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
        case ImageFormat::RGBA32_UNORM:
            return GL_RGB32UI;
        }

        MC_CORE_ASSERT(false);
        return 0;
    }

}

OpenGL33Texture::OpenGL33Texture(const TextureSpecification& specification, AssetHandle handle, Buffer data)
    : Texture(0)
    , m_Specification(specification)
    , m_Width(m_Specification.Width)
    , m_Height(m_Specification.Height)
{
    Handle = handle;
    MC_PROFILE_SCOPE_NAME("(Texture) Constructor");

    m_InternalFormat = Utils::MaineCoonImageFormatToGLInternalFormat(m_Specification.Format);
    m_DataFormat = Utils::MaineCoonImageFormatToGLDataFormat(m_Specification.Format);

    GL33::GL()->PixelStorei(GL_UNPACK_ALIGNMENT, m_Specification.UnpackAlignment);

    GL33::GL()->GenTextures(1, &m_RendererID);
    GL33::GL()->BindTexture(GL_TEXTURE_2D, m_RendererID);

    GL33::GL()->TexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    if (m_Specification.GenerateMips) {

        GL33::GL()->GenerateMipmap(GL_TEXTURE_2D);

        GL33::GL()->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        GL33::GL()->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        GL33::GL()->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        GL33::GL()->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    } else {

        GL33::GL()->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        GL33::GL()->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        GL33::GL()->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        GL33::GL()->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    if (data)
        SetData(data);
}

OpenGL33Texture::~OpenGL33Texture()
{
    Destroy();
}

void OpenGL33Texture::SetData(Buffer data)
{
    MC_PROFILE_SCOPE_NAME("(Texture) Set data");

    // uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;
    // MC_CORE_ASSERT_TAGGED(data.Size == m_Width * m_Height * bpp, "Data must be the entire texture!");

    GL33::GL()->BindTexture(GL_TEXTURE_2D, m_RendererID);
    GL33::GL()->TexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data.Data);

    if (m_Specification.GenerateMips)
        GL33::GL()->GenerateMipmap(GL_TEXTURE_2D);
}

void OpenGL33Texture::SetSubData(void* data, uint32_t width, uint32_t height)
{
    MC_PROFILE_SCOPE_NAME("(Texture) Set sub data");

    GL33::GL()->BindTexture(GL_TEXTURE_2D, m_RendererID);
    GL33::GL()->TexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, m_DataFormat, GL_UNSIGNED_BYTE, data);

    if (m_Specification.GenerateMips)
        GL33::GL()->GenerateMipmap(GL_TEXTURE_2D);
}

void OpenGL33Texture::Bind(uint32_t slot) const
{
    MC_PROFILE_SCOPE_NAME("(Texture) bind");

    GL33::GL()->ActiveTexture(GL_TEXTURE0 + slot);
    GL33::GL()->BindTexture(GL_TEXTURE_2D, m_RendererID);
}

void OpenGL33Texture::Destroy()
{
    MC_PROFILE_SCOPE_NAME("(Textures) Delete");

    GL33::GL()->DeleteTextures(1, &m_RendererID);
}
}

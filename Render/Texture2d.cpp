#include <Render/Texture2d.h>
#include <Render/Context.h>
#include <cassert>

namespace Commons
{
	namespace Render
	{
		static void TranslateFormat(Texture::FormatMode format, GLenum& glFormat, GLenum& glInternalFormat)
		{
			switch (format)
			{
			case Commons::Render::Texture::FORMAT_RGBA:
				glFormat = GL_RGBA;
				glInternalFormat = GL_RGBA;
				break;
			case Commons::Render::Texture::FORMAT_RGB:
				glFormat = GL_RGB;
				glInternalFormat = GL_RGB;
				break;
			case Texture::FORMAT_LUMINANCE:
				glFormat = GL_LUMINANCE;
				glInternalFormat = GL_LUMINANCE;
			case Texture::FORMAT_ALPHA:
				glFormat = GL_ALPHA;
				glInternalFormat = GL_ALPHA;
			default:
				assert("Unsupported texture format");
			}
		}

		Texture2d::Texture2d(Context* context)
			: Texture(context)
        {
		}

		Texture2d::~Texture2d()
		{
		}

        void Texture2d::setData(uint32_t level, FormatMode format, uint32_t width, uint32_t height, const uint8_t* pixels)
        {
			// TODO: assert bound?
            //bind(); // TODO: check if bound already?
            GLenum glFormat, glInternalFormat;
            TranslateFormat(format, glFormat, glInternalFormat);
            ::glTexImage2D(GL_TEXTURE_2D, level, glInternalFormat, width, height, 0, glFormat, GL_UNSIGNED_BYTE, pixels);
            CHECK_GL_ERROR();
        }

        void Texture2d::setSubData(uint32_t level, FormatMode format, uint32_t x, uint32_t y, uint32_t width, uint32_t height, const uint8_t* pixels)
        {
            bind(); // TODO: check if bound already?
            GLenum glFormat, glInternalFormat; // TODO: cache format
            TranslateFormat(format, glFormat, glInternalFormat);
            ::glTexSubImage2D(GL_TEXTURE_2D, level, x, y, width, height, glFormat, GL_UNSIGNED_BYTE, pixels);
            CHECK_GL_ERROR();
        }
    }
}
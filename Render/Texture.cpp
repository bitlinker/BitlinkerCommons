#include <Render/Texture.h>
#include <Render/GLContext.h>
#include <cassert>

namespace Commons
{
	namespace Render
	{
        static GLenum TranslateFilterMode(Texture::FilterMode filterMode)
        {
            switch (filterMode)
            {
            case Texture::FILTER_NEAREST: return GL_NEAREST;
            case Texture::FILTER_LINEAR: return GL_LINEAR;
            case Texture::FILTER_LINEAR_MIPMAP_LINEAR: return GL_LINEAR_MIPMAP_LINEAR;
            default:
                assert("Unsupported filter mode");
                return GL_LINEAR;
            }
        }

        static GLenum TranslateWrapMode(Texture::WrapMode wrapMode)
        {
            switch (wrapMode)
            {
            case Texture::WRAP_REPEAT: return GL_REPEAT;
            case Texture::WRAP_CLAMP: return GL_CLAMP;
            default:
                assert("Unsupported wrap mode");
                return GL_REPEAT;
            }
        }

		Texture::Texture()
			: mTex(0)
            , mMinFilter(TranslateFilterMode(FILTER_LINEAR))
            , mMagFilter(TranslateFilterMode(FILTER_LINEAR))
            , mWrapS(TranslateWrapMode(WRAP_REPEAT))
            , mWrapT(TranslateWrapMode(WRAP_REPEAT))
            , mStateDirty(true)
        {
			::glGenTextures(1, &mTex);
            CHECK_GL_ERROR();
		}

		Texture::~Texture()
		{
			::glDeleteTextures(1, &mTex);
            CHECK_GL_ERROR();
		}

		void Texture::bind()
		{
			::glBindTexture(GL_TEXTURE_2D, mTex);
            CHECK_GL_ERROR();
            refreshState();            
		}

		void Texture::unbind()
		{
			::glBindTexture(GL_TEXTURE_2D, 0);
            CHECK_GL_ERROR();
		}

        void Texture::refreshState()
        {
            if (mStateDirty)
            {                
                ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mMinFilter);
                ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mMagFilter);
                ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mWrapS);
                ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mWrapT);
                CHECK_GL_ERROR();
                mStateDirty = false;
            }
        }

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

        void Texture::setData(uint32_t level, FormatMode format, uint32_t width, uint32_t height, const uint8_t* pixels)
        {
            bind(); // TODO: check if bound already?
            GLenum glFormat, glInternalFormat;
            TranslateFormat(format, glFormat, glInternalFormat);
            ::glTexImage2D(GL_TEXTURE_2D, level, glInternalFormat, width, height, 0, glFormat, GL_UNSIGNED_BYTE, pixels);
            CHECK_GL_ERROR();
        }

        void Texture::setSubData(uint32_t level, FormatMode format, uint32_t x, uint32_t y, uint32_t width, uint32_t height, const uint8_t* pixels)
        {
            bind(); // TODO: check if bound already?
            GLenum glFormat, glInternalFormat; // TODO: cache format
            TranslateFormat(format, glFormat, glInternalFormat);
            ::glTexSubImage2D(GL_TEXTURE_2D, level, x, y, width, height, glFormat, GL_UNSIGNED_BYTE, pixels);
            CHECK_GL_ERROR();
        }
    
        void Texture::setFilters(FilterMode minFilter, FilterMode magFilter)
        {
            mMinFilter = TranslateFilterMode(minFilter);
            mMagFilter = TranslateFilterMode(magFilter);
            mStateDirty = true;            
        }

        void Texture::setWrap(WrapMode wrapS, WrapMode wrapT)
        {
            mWrapS = TranslateWrapMode(wrapS);
            mWrapT = TranslateWrapMode(wrapT);
            mStateDirty = true;
        }

        void Texture::setMipLevels(uint32_t base, uint32_t max)
        {
            bind(); // TODO: eliminate texture binding?
            ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, base);
            ::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, max);
            CHECK_GL_ERROR();
        }
    }
}
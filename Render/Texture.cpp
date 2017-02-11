#include <Render/Texture.h>
#include <Render/Context.h>
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
            case Texture::WRAP_CLAMP_TO_EDGE: return GL_CLAMP_TO_EDGE;
            default:
                assert("Unsupported wrap mode");
                return GL_REPEAT;
            }
        }

		Texture::Texture(Context* context)
			: mContext(context)
            , mTex(0)
            , mMinFilter(TranslateFilterMode(FILTER_LINEAR))
            , mMagFilter(TranslateFilterMode(FILTER_LINEAR))
            , mWrapS(TranslateWrapMode(WRAP_REPEAT))
            , mWrapT(TranslateWrapMode(WRAP_REPEAT))
            , mStateDirty(true)
        {
            mContext->genTexture();
		}

		Texture::~Texture()
		{
            mContext->deleteTexture(mTex);			
		}

		void Texture::bind()
		{
            mContext->bindTexture(mTex);
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
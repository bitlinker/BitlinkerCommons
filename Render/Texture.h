#pragma once
#include <Render/RenderCommon.h>
#include <Render/IBindable.h>
#include <Common/NonCopyable.h>
#include <memory>

namespace Commons
{
	namespace Render
	{
		class Texture : public IBindable, public NonCopyable
		{
        public:
            enum FilterMode
            {
                FILTER_NEAREST,
                FILTER_LINEAR,
                FILTER_LINEAR_MIPMAP_LINEAR,
            };

            enum WrapMode
            {
                WRAP_REPEAT,
                WRAP_CLAMP_TO_EDGE,
            };

            enum FormatMode
            {
                FORMAT_RGBA,
                FORMAT_RGB,
                FORMAT_LUMINANCE,
                FORMAT_ALPHA,
            };

		public:
            // TODO: rename to texture2d
            // TODO: construct from image data
			Texture(); // TODO: private constructor, create in context only
			virtual ~Texture();

			void setFilters(FilterMode minFilter, FilterMode magFilter);
            void setWrap(WrapMode wrapS, WrapMode wrapT);
            void setMipLevels(uint32_t start, uint32_t end);

            void setData(uint32_t level, FormatMode format, uint32_t width, uint32_t height, const uint8_t* pixels);
            void setSubData(uint32_t level, FormatMode format, uint32_t x, uint32_t y, uint32_t width, uint32_t height, const uint8_t* pixels);

			virtual void bind() override;
			virtual void unbind() override;

        private:
            void refreshState();

		private:
			GLuint mTex;

            // State:
            GLenum mMinFilter;
            GLenum mMagFilter;
            GLenum mWrapS;
            GLenum mWrapT;
            bool mStateDirty;
		};

		typedef std::shared_ptr<Texture> TexturePtr;
		typedef std::weak_ptr<Texture> TextureWeakPtr;
	}
}

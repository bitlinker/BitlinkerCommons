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
			Texture();
			virtual ~Texture();

			void setMinFilter(GLenum filter);
			void setMagFilter(GLenum filter);

			void setTexData2d(GLint level, GLint internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels);

			virtual void bind();
			virtual void unbind();

		private:
			GLuint m_tex;
		};

		typedef std::shared_ptr<Texture> TexturePtr;
		typedef std::weak_ptr<Texture> TextureWeakPtr;
	}
}

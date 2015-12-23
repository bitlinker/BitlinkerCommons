#include <Render/Texture.h>

namespace Commons
{
	namespace Render
	{
		Texture::Texture()
			: mTex(0)
		{
			::glGenTextures(1, &mTex);
		}


		Texture::~Texture()
		{
			::glDeleteTextures(1, &mTex);
		}

		void Texture::bind()
		{
			::glBindTexture(GL_TEXTURE_2D, mTex);
		}

		void Texture::unbind()
		{
			::glBindTexture(GL_TEXTURE_2D, 0);
		}

		void Texture::setMinFilter(GLenum filter)
		{
			bind(); // TODO: check if bound already?
			::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		}

		void Texture::setMagFilter(GLenum filter)
		{
			bind(); // TODO: check if bound already?
			::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}

		void Texture::setTexData2d(GLint level, GLint internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *pixels)
		{
			bind(); // TODO: check if bound already?
			::glTexImage2D(GL_TEXTURE_2D, level, internalformat, width, height, 0, format, type, pixels);
			// TODO: force set filters & clamp mode?
		}
	}
}
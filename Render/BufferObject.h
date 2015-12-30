#pragma once
#include <Common/NonCopyable.h>
#include <Render/RenderCommon.h>
#include <Render/IBindable.h>
namespace Commons
{
	namespace Render
	{
		/**
		* OpenGL buffer object wrapper
		*/
		class BufferObject : public IBindable, public NonCopyable
		{
		public:
			BufferObject(GLenum type)
				: m_handle(0)
				, m_type(type)
			{
				::glGenBuffers(1, &m_handle);
                CHECK_GL_ERROR();
			}

			virtual ~BufferObject()
			{
				::glDeleteBuffers(1, &m_handle);
                CHECK_GL_ERROR();
			}

			void setData(GLsizeiptr size, const void* data, GLenum usage)
			{
				bind(); // TODO: check if bound already?
				::glBufferData(m_type, size, data, usage);
                CHECK_GL_ERROR();
			}

			GLuint get() const
			{
				return m_handle;
			}

			virtual void bind() override
			{
				::glBindBuffer(m_type, m_handle);
                CHECK_GL_ERROR();
			}

			virtual void unbind() override
			{
				::glBindBuffer(m_type, 0);
                CHECK_GL_ERROR();
			}


		private:
			GLuint m_handle;
			GLenum m_type;
		};
	}
}

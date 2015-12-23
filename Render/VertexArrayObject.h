#pragma once
#include <Common/NonCopyable.h>
#include <Render/RenderCommon.h>
#include <Render/IBindable.h>

namespace Commons
{
	namespace Render
	{
		/**
		* OpenGL vertex array object wrapper
		*/
		class VertexArrayObject : public IBindable, public NonCopyable
		{
		public:
			VertexArrayObject()
			{
				::glGenVertexArrays(1, &m_handle);
			}

			virtual ~VertexArrayObject()
			{
				::glDeleteVertexArrays(1, &m_handle);
			}

			GLuint get() const
			{
				return m_handle;
			}

			virtual void bind() override
			{
				::glBindVertexArray(m_handle);
			}

			virtual void unbind() override
			{
				::glBindVertexArray(0);
			}

		private:
			GLuint m_handle;
		};
	}
}

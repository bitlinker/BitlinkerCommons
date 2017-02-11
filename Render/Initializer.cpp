#include <Render/RenderCommon.h>
#include <Render/Initializer.h>
#include <Exception/Exception.h>

namespace Commons
{
	namespace Render
	{
		void Initializer::Init()
		{
			if (GL_TRUE != ::glfwInit())
				throw Commons::UnknownException("Can't init GLFW");
		}

		void Initializer::Destroy()
		{
			::glfwTerminate();
		}

		ScopedInitializer::ScopedInitializer()
		{
			Initializer::Init();
		}

		ScopedInitializer::~ScopedInitializer()
		{
			Initializer::Destroy();
		}
	}
}
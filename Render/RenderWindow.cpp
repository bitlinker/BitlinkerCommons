#include <Render/RenderWindow.h>
#include <Exception/exception.h>
#include <Logger/Log.h>

namespace Commons
{
	namespace Render
	{
		RenderWindow::RenderWindow(const WindowParams& params)
		{
			// TODO: options

			// FSAA
			//::glfwWindowHint(GLFW_SAMPLES, 16);

			::glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
			::glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);

			//::glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
			//::glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

			::glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		    ::glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			// TODO: monitor & res selection
			GLFWmonitor* mon = ::glfwGetPrimaryMonitor();
			const GLFWvidmode* mode = ::glfwGetVideoMode(mon);

			m_window = std::shared_ptr<GLFWwindow>(::glfwCreateWindow(params.width, params.height, params.title.c_str(), NULL, NULL), ::glfwDestroyWindow);
			if (m_window == nullptr)
				throw Commons::UnknownException("Can't create GLFW window");
			::glfwMakeContextCurrent(m_window.get());
			::glfwSetWindowUserPointer(m_window.get(), this);

			//::glfwSetInputMode(m_window.get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			//::glfwSetCursorPosCallback(m_window.get(), CursorCallbackStatic); // TODO: not needed? (have events)

			initGLEW();
		}

		RenderWindow::~RenderWindow()
		{
		}

		//void Render::cursorCallback(double xpos, double ypos)
		//{
		//	printf("Mouse: %f, %f\n", xpos, ypos);
		//	// TODO: process input
		//}

		void RenderWindow::initGLEW()
		{
			// GLEW
			glewExperimental = GL_TRUE;
			if (GLEW_OK != ::glewInit())
				throw Commons::UnknownException("Can't init GLEW");

			const GLubyte* renderer = ::glGetString(GL_RENDERER); // get renderer string
			const GLubyte* version = ::glGetString(GL_VERSION); // version as a string

			LOG_DEBUG("Renderer: %s, version: %s", renderer, version);
		}

		bool RenderWindow::tick()
		{
			if (::glfwWindowShouldClose(m_window.get()))
				return false;

			::glfwPollEvents();
			return true;
		}

		double RenderWindow::getCurTime() const
		{
			return ::glfwGetTime();
		}

		void RenderWindow::swapBuffers()
		{
			::glfwSwapBuffers(m_window.get());
		}

		void RenderWindow::getFramebufferSize(uint32_t& width, uint32_t& height) const
		{
			int w, h;
			::glfwGetFramebufferSize(m_window.get(), &w, &h);
			width = static_cast<uint32_t>(w);
			height = static_cast<uint32_t>(h);
		}
		// TODO
	}
}
#pragma once
#include <Render/RenderCommon.h>
#include <Common/NonCopyable.h>
#include <memory>

namespace Commons
{
	namespace Render
	{
		class WindowParams
		{
		public:
			uint32_t width;
			uint32_t height;
			std::string title;
			//bool isFullscreen; // TODO: monitor number

			// GL window settings
			uint32_t fsaaSamples;
			uint32_t contextMajor;
			uint32_t contextMinor;
			bool isForwardCompat;
		};

		class RenderWindow : public NonCopyable
		{
		public:
			RenderWindow(const WindowParams& params);
			~RenderWindow();

			bool tick();
			// TODO: make it framebuffer interace?
			void swapBuffers();
			void getFramebufferSize(uint32_t& width, uint32_t& height) const;

			double getCurTime() const;

		private:
			void initGLEW();

		private:
			std::shared_ptr<GLFWwindow> m_window;
		};
	}
}

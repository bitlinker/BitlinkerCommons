#pragma once
#include <Render/RenderCommon.h>
#include <Render/Context.h>
#include <Common/NonCopyable.h>
#include <memory>

namespace Commons
{
	namespace Render
	{
		// TODO: params
		class WindowParams
		{
		public:
			uint32_t width;
			uint32_t height;
			std::string title;
            //uint32_t fullscreenMonitorId;  // TODO: monitor number for fullscreen
			bool isFullscreen;

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
			void swapBuffers();

			Context* getContextPtr() { return &mContext; }

			void getFramebufferSize(uint32_t& width, uint32_t& height) const;
			void getFramebuffer() {}; // TODO: impl

		private:
			void initGLEW();

		private:
			std::shared_ptr<GLFWwindow> m_window;
			Context mContext;
		};
	}
}

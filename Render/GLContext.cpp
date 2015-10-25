#include <Render/GLContext.h>
#include <Exception/Exception.h>
#include <Logger/Log.h>

namespace Commons
{
	namespace Render
	{
		GLContext::GLContext()
		{
		}

		GLContext::~GLContext()
		{
		}

		/*void Render::updateCameraUniforms(const CameraPtr& camera)
		{
			glm::mat4 modelMatrix; // Store the model matrix       // TODO
			modelMatrix = glm::mat4(1.0f);

			glm::mat4 mvpMatrix = camera->getProjection() * camera->getModelview() * modelMatrix;


			bool u = m_shader->use();
			m_shader->setUniformMatrix(m_uMVP, mvpMatrix);
		}*/

		// TODO: clear func, state funcs

		void GLContext::render(const CameraPtr& camera, const RenderNodePtr& rootNode, const RenderWindow& window)
		{
			//_update_fps_counter(m_window.get());

			//updateCameraUniforms(camera);


			// TODO: viewport from framebuffer, cache
			float ratio;
			uint32_t width, height;
			window.getFramebufferSize(width, height);
			ratio = width / (float)height;
			::glViewport(0, 0, width, height);
			::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// TODO: use culling here?
			glm::mat4 camMatrix = camera->getProjection() * camera->getModelview();
			rootNode->render(camMatrix);
		}
	}
}
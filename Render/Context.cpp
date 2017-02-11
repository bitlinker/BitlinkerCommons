#include <Render/Context.h>
#include <Render/RenderWindow.h>
#include <Exception/Exception.h>
#include <Logger/Log.h>

namespace Commons
{
	namespace Render
	{
		Context::Context()
            : mCurShader(0)
            , mCurTexture(0)
		{
		}

		Context::~Context()
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

		void Context::render(const CameraPtr& camera, const RenderNodePtr& rootNode, const RenderWindow& window)
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

        static void enableOption(bool enabled, GLenum option)
        {
            enabled ? ::glEnable(option) : ::glDisable(option);
            CHECK_GL_ERROR();
        }

        void Context::setBlend(bool enabled)
        {
            // TODO: cache?
            enableOption(enabled, GL_BLEND);
        }

        void Context::setCullFace(bool enabled)
        {
            enableOption(enabled, GL_CULL_FACE);
        }

        void Context::setDepthTest(bool enabled)
        {
            enableOption(enabled, GL_DEPTH_TEST);
        }

        //void GLContext::bindShader(const ShaderProgram* shader)
        //{
        //    //assert(shader);
        //    //if (shader->getProgram() != mCurShader)
        //    //{
        //    //    shader->use(); // TODO: context...
        //    //    mCurShader = shader->get();                
        //    //}
        //}

        //// Bind buffer


        GLuint Context::genTexture()
        {
            GLuint tex = 0;
            ::glGenTextures(1, &tex);
            CHECK_GL_ERROR();
            return tex;
        }

        void Context::deleteTexture(GLuint tex)
        {
            ::glDeleteTextures(1, &tex);
            CHECK_GL_ERROR();
        }

        void Context::bindTexture(GLuint tex)
        {
			// TODO: in texture
            // TODO: drop current texture on state change
            if (mCurTexture != tex)
            {
                ::glBindTexture(GL_TEXTURE_2D, tex);
                CHECK_GL_ERROR();
                mCurTexture = tex;
            }           
        }
	}
}
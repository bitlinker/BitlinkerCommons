#pragma once

#include <memory>
#include <Render/RenderCommon.h>
#include <Render/RenderNode.h>
#include <Render/Camera.h>

#include <Render/Texture.h>
#include <Render/Shader.h>
#include <Render/ShaderProgram.h>

// TODO: build params
#define GL_DEBUG

#ifdef GL_DEBUG
#   define CHECK_GL_ERROR() assert(::glGetError() == 0);
#else
#   define CHECK_GL_ERROR()
#endif

namespace Commons
{
	namespace Render
	{
		class RenderWindow;

		class Context
		{
            friend class Texture;
		public:
			Context();
			~Context();

			bool tick(float fTimeDelta);
			// TODO: and framebuffer
            // TODO: move
			void render(const CameraPtr& camera, const RenderNodePtr& rootNode, const RenderWindow& window);


            // State machine:
            void setBlend(bool isEnabled);
            void setCullFace(bool isEnabled);
            void setDepthTest(bool isEnabled);

        private:
            // To be used by context friend classes:
            // TODO: custom context impl
            GLuint genTexture();
            void deleteTexture(GLuint tex);
            void bindTexture(GLuint tex);

            //void bindShader(const ShaderProgram* shader);

		private:
            GLuint mCurTexture; // TODO: for each sampler
            GLuint mCurShader;
		};
	}
}
#pragma once

#include <memory>
#include <Render/RenderCommon.h>
#include <Render/RenderNode.h>
#include <Render/Camera.h>
#include <Render/RenderWindow.h>

#include <Render/Texture.h>
#include <Render/Shader.h>
#include <Render/ShaderProgram.h>

namespace Commons
{
	namespace Render
	{
		class GLContext
		{
		public:
			GLContext();
			~GLContext();

			bool tick(float fTimeDelta);
			// TODO: and framebuffer
			void render(const CameraPtr& camera, const RenderNodePtr& rootNode, const RenderWindow& window);

			// TODO: create all GL-related resources here...
			// Use some loader as parameter
			TexturePtr createTexture();
			ShaderPtr createShader();
			ShaderProgramPtr createShaderProgram();

		private:
		};
	}
}
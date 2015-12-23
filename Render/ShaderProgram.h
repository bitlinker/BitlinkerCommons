#pragma once
#include <Render/RenderCommon.h>
#include <Render/Shader.h>
#include <set>

namespace Commons
{
	namespace Render
	{
		// TODO: type for attributes

		class ShaderProgram
		{
		public:
			ShaderProgram();
			~ShaderProgram();

			bool attach(const ShaderPtr& shader);
			bool detach(const ShaderPtr& shader);

			bool link();
			bool validate();
			void getInfoLog(std::string& log);

			bool use(); // TODO: ibindable?

			uint32_t getNumAttributes();
			uint32_t getAttribute(uint32_t index);
			uint32_t getAttributeLocation(const std::string& name);

			uint32_t getNumUniforms();
			uint32_t getUniform(uint32_t index);
			uint32_t getUniformLocation(const std::string& name);

			bool setUniformMatrix(uint32_t index, const glm::mat4& mat);
			bool setUniformSampler2D(uint32_t index, uint32_t samplerId);
            bool setUniformFloat(uint32_t index, float value);
            bool setUniformVec2(uint32_t index, const glm::vec2& vec);
            bool setUniformVec3(uint32_t index, const glm::vec3& vec);

		private:
			bool checkValidateStatus();
			bool checkLinkStatus();


		private:
			GLuint m_program;
			std::set<ShaderPtr> attachedShaders;

			bool isLinked;
			bool isValidated;
		};

		typedef std::shared_ptr<ShaderProgram> ShaderProgramPtr;
	}
}

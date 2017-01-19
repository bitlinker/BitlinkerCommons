#pragma once
#include <Render/RenderCommon.h>
#include <Render/Frustum.h>
#include <memory>

namespace Commons
{
	namespace Render
	{
        /*
        * The initial camera orientation is following:
        * x axis - left,
        * y axis - up,
        * z axis - backwards
        */
		class Camera
		{
		public:
			Camera();
			~Camera();

			void setPerspective(float fovy, float aspect, float far, float near);
			void setOrtho(float left, float top, float right, float bottom, float far, float near);

			const glm::mat4 getProjection() const { return m_proj; };
			const glm::mat4 getModelview() const;
            const glm::mat4 getMatrix() const;

			const glm::vec3 getTranslation() const;
			void setTranslation(const glm::vec3& pos);

			const glm::quat getRotation() const;
			void setRotation(const glm::quat& rotation);

            const Frustum& getFrustum() const;

		private:
			glm::mat4 m_proj;

			glm::vec3 mPos;
			glm::quat m_rot;

			// Matrix cache
			mutable glm::mat4 mModelView;
			mutable bool mIsModelViewDirty;

            // Frustum cache
            mutable Frustum mFrustum;
            mutable bool mIsFrustumDirty;
		};

		typedef std::shared_ptr<Camera> CameraPtr;
	}
}

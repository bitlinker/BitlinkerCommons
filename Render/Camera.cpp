#include <Render/Camera.h>

namespace Commons
{
	namespace Render
	{
		Camera::Camera()
			: m_proj()
			, m_pos()
			, m_rot()
			, mIsModelViewDirty(true)
            , mFrustum()
            , mIsFrustumDirty(true)
		{
		}

		Camera::~Camera()
		{
		}

		// TODO: separate perspective and ortho camera?

		void Camera::setPerspective(float fovy, float aspect, float far, float near)
		{
			m_proj = glm::perspective(fovy, aspect, near, far);
            mIsFrustumDirty = true;
		}

		void Camera::setOrtho(float left, float top, float right, float bottom, float far, float near)
		{
			m_proj = glm::ortho(left, right, bottom, top, near, far);
            mIsFrustumDirty = true;
		}

		const glm::vec3 Camera::getTranslation() const
		{
			return m_pos;
		}

		void Camera::setTranslation(const glm::vec3& pos)
		{
			m_pos = pos;
			mIsModelViewDirty = true;
            mIsFrustumDirty = true;
		}

		const glm::quat Camera::getRotation() const
		{
			return m_rot;
		}

		void Camera::setRotation(const glm::quat& rotation)
		{
			m_rot = rotation;
			mIsModelViewDirty = true;
            mIsFrustumDirty = true;
		}

		const glm::mat4 Camera::getModelview() const
		{
			if (mIsModelViewDirty)
			{
				mModelView = glm::mat4(); // TODO: optimize
                mModelView *= glm::mat4_cast(-m_rot);
                mModelView *= glm::translate(-m_pos);
				mIsModelViewDirty = false;
			}
			return mModelView;
		}

        const glm::mat4 Camera::getMatrix() const
        {
            return getProjection() * getModelview();
        }

        const Frustum& Camera::getFrustum() const 
        {
            if (mIsFrustumDirty)
            {
                mFrustum.setFromCamMatrix(getMatrix());
                mIsFrustumDirty = false;
            }
            return mFrustum;
        }
	}
}
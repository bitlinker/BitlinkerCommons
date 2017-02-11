#include <Render/Camera.h>

namespace Commons
{
	namespace Render
	{
		CameraPtr Camera::MakePerspectiveCamera(float fovy, float aspect, float far, float near)
		{
			CameraPtr result = CameraPtr(new Camera());
			result->setPerspective(fovy, aspect, far, near);
			return result;
		}

		CameraPtr Camera::MakeOrthoCamera(float left, float top, float right, float bottom, float far, float near)
		{
			CameraPtr result = CameraPtr(new Camera());
			result->setOrtho(left, top, right, bottom, far, near);
			return result;
		}

		Camera::Camera()
			: m_proj()
			, mPos()
			, m_rot()
			, mIsModelViewDirty(true)
            , mFrustum()
            , mIsFrustumDirty(true)
		{
		}

		Camera::~Camera()
		{
		}

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
			return mPos;
		}

		void Camera::setTranslation(const glm::vec3& pos)
		{
			mPos = pos;
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
                mModelView *= glm::translate(-mPos);
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
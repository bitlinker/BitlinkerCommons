#pragma once
#include <Render/RenderCommon.h>
#include <Render/AABB.h>

namespace Commons
{
	namespace Render
	{
        // TODO: move?
        class Plane
        {
        public:
            Plane()
                : mNormal()
                , mDist(0)
            {
            }

            Plane(const glm::vec3& normal, float dist)
            {
                setAndNormalize(normal, dist);
            }

            void set(const glm::vec3& normal, float dist)
            {
                mNormal = normal;
                mDist = dist;
            }

            void normalize()
            {
                auto invLen = 1.F / mNormal.length();
                mNormal /= invLen;
                mDist /= invLen;
            }

            void setAndNormalize(const glm::vec3& normal, float dist)
            {
                set(normal, dist);
                normalize();
            }

            inline float getDist(const glm::vec3& point) const
            {
                return glm::dot(mNormal, point) + mDist;
            }

        public:
            glm::vec3 mNormal;
            float mDist;
        };

		class Frustum
		{
		public:
            Frustum();
            Frustum(const glm::mat4& m);
            void setFromCamMatrix(const glm::mat4& m);

            bool isInFrustum(const AABB& aabb) const;
            bool isInFrustum(const glm::vec3& pos, float radius) const;

        private:
            enum PlaneEnum
            {
                Plane_MIN = 0,
                PlaneTop = Plane_MIN,
                PlaneBottom,
                PlaneLeft,
                PlaneRight,
                PlaneNear,
                PlaneFar,
                Plane_MAX
            };

            Plane mPlanes[Plane_MAX];
		};
	}
}

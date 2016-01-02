#pragma once
#include <Render/Frustum.h>

namespace Commons
{
	namespace Render
	{
        Frustum::Frustum()
            : mPlanes()
        {
        }
        
        Frustum::Frustum(const glm::mat4& m)
            : mPlanes()
        {
            setFromCamMatrix(m);
        }

        void Frustum::setFromCamMatrix(const glm::mat4& m)
        {
            glm::vec4 offset(
                m[0][3],
                m[1][3],
                m[2][3],
                m[3][3]);
            mPlanes[PlaneNear].setAndNormalize(
                glm::vec3(  m[0][2],
                            m[1][2],
                            m[2][2]) + glm::vec3(offset),
                            m[3][2] + offset.w);
            mPlanes[PlaneFar].setAndNormalize(
                glm::vec3(  -m[0][2],
                            -m[1][2],
                            -m[2][2]) + glm::vec3(offset),
                            -m[3][2] + offset.w);
            mPlanes[PlaneBottom].setAndNormalize(
                glm::vec3(  m[0][1],
                            m[1][1],
                            m[2][1]) + glm::vec3(offset),
                            m[3][1] + offset.w);
            mPlanes[PlaneTop].setAndNormalize(
                glm::vec3(  -m[0][1],
                            -m[1][1],
                            -m[2][1]) + glm::vec3(offset),
                            -m[3][1] + offset.w);
            mPlanes[PlaneLeft].setAndNormalize(
                glm::vec3(  m[0][0],
                            m[1][0],
                            m[2][0]) + glm::vec3(offset),
                            m[3][0] + offset.w);
            mPlanes[PlaneRight].setAndNormalize(
                glm::vec3(  -m[0][0],
                            -m[1][0],
                            -m[2][0]) + glm::vec3(offset),
                            -m[3][0] + offset.w);
        }

        bool Frustum::isInFrustum(const AABB& aabb) const
        {
            bool result = true;
            int32_t out, in;
            for (uint32_t i = Plane_MIN; i < Plane_MAX; ++i)
            {
                out = 0; in = 0;                
                for (int k = 0; k < 8 && (in == 0 || out == 0); ++k)
                {
                    if (mPlanes[i].getDist(aabb.getVertex(k)) < 0)
                    {
                        ++out;
                    }
                    else
                    {
                        --in;
                    }
                }
                if (!in)
                {
                    return false;
                }
                else if (out)
                {
                    result = true; // Intersects
                }
            }
            return result;
        }

        bool Frustum::isInFrustum(const glm::vec3& pos, float radius) const
        {
            float distance;
            bool result = true;
            for (uint32_t i = Plane_MIN; i < Plane_MAX; ++i)
            {
                distance = mPlanes[i].getDist(pos);
                if (distance < -radius)
                {
                    return false;
                }
                else if (distance < radius)
                {
                    result = true; // Intersects
                }
            }

            return result;
        }
	}
}

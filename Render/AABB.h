#pragma once
#include <Render/RenderCommon.h>
#include <memory>

namespace Commons
{
	namespace Render
	{
		class AABB
		{
		public:			
			AABB()
				: mMins()
				, mMaxs()
			{
			}

			// TODO: rm this constructor
			AABB(const int16_t mins[3], const int16_t maxs[3])
                : mMins(mins[0], mins[1], mins[2])
                , mMaxs(maxs[0], maxs[1], maxs[2])
            {                
            }

			AABB(const glm::vec3& mins, const glm::vec3& maxs)
				: mMins(mins)
				, mMaxs(maxs)
			{
			}

			bool isEmpty()
			{
				return mMins[0] == mMaxs[0] || mMins[1] == mMaxs[1] || mMins[2] == mMaxs[2];
			}

            /*
            * Oder: bottom plane then top plane, starting from min point clockwise
            */
            const glm::vec3 getVertex(uint32_t index) const
            {
                assert(index < 8);
                switch (index)
                {
                case 0:
                    return mMins;
                case 1:
                    return glm::vec3(mMins.x, mMins.y, mMaxs.z);
                case 2:
                    return glm::vec3(mMaxs.x, mMins.y, mMaxs.z);
                case 3:
                    return glm::vec3(mMaxs.x, mMins.y, mMins.z);
                case 4:
                    return glm::vec3(mMins.x, mMaxs.y, mMins.z);
                case 5:
                    return glm::vec3(mMins.x, mMaxs.y, mMaxs.z);
                case 6:
                    return mMaxs;
                case 7:
                    return glm::vec3(mMaxs.x, mMaxs.y, mMins.z);
                }                
                return mMins;
            }

		public:
			glm::vec3 mMins;
            glm::vec3 mMaxs;
		};
	}
}

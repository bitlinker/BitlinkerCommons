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
			AABB(const int16_t mins[3], const int16_t maxs[3])
                : mMins(mins[0], mins[1], mins[2])
                , mMaxs(maxs[0], maxs[1], maxs[2])
            {                
            }

		public:
			glm::vec3 mMins;
            glm::vec3 mMaxs;
		};
	}
}

#pragma once
#include <Imaging/IInterpolator.h>

namespace Commons
{
	namespace Imaging
	{
		class BilinearInterpolator : public IInterpolator
		{
		public:
            virtual bool interpolateImage(const uint8_t* src, const ImageInfo& srcInfo, uint8_t *dst, const ImageInfo& dstInfo);

            virtual ~BilinearInterpolator() {};
		};
	}
}

#pragma once
#include <stdint.h>
#include <Imaging/ImageInfo.h>
#include <memory>

namespace Commons
{
	namespace Imaging
	{
        class IInterpolator
        {
        public:
            virtual bool interpolateImage(const uint8_t* src, const ImageInfo& srcInfo,  uint8_t *dst, const ImageInfo& dstInfo) = 0;

            virtual ~IInterpolator() {}
        };

        typedef std::shared_ptr<IInterpolator> IInterpolatorPtr;
	}
}

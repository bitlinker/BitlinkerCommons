#pragma once
#include <Imaging/BilinearInterpolator.h>
#include <cassert>

namespace Commons
{
	namespace Imaging
	{
        bool BilinearInterpolator::interpolateImage(const uint8_t* src, const ImageInfo& srcInfo, uint8_t *dst, const ImageInfo& dstInfo)
        {
            assert(srcInfo.getNumChannels() == dstInfo.getNumChannels());

            uint32_t a, b, c, d, x, y, index;
            float tx = (float)(srcInfo.getWidth() - 1) / dstInfo.getWidth();
            float ty = (float)(srcInfo.getHeight() - 1) / dstInfo.getHeight();
            float x_diff, y_diff;
            const uint32_t srcStride = srcInfo.getScanlineSize();
            const uint32_t dstStride = dstInfo.getScanlineSize();
            const uint32_t numChannels = dstInfo.getNumChannels();

            for (uint32_t i = 0; i < dstInfo.getHeight(); ++i)
            {
                for (uint32_t j = 0; j < dstInfo.getWidth(); ++j)
                {
                    x = (int32_t)(tx * j);
                    y = (int32_t)(ty * i);

                    x_diff = ((tx * j) - x);
                    y_diff = ((ty * i) - y);

                    index = srcInfo.getPixelOffset(x, y);
                    a = (int32_t)index;
                    b = (int32_t)(index + numChannels);
                    c = (int32_t)(index + srcStride);
                    d = (int32_t)(index + srcStride + numChannels);

                    // TODO: make fixed point calculations
                    for (uint32_t k = 0; k < numChannels; k++)
                    {
                        dst[dstInfo.getPixelOffset(j, i) + k] = (uint8_t)(
                            src[a + k] * (1.F - x_diff) * (1.F - y_diff)
                            + src[b + k] * (1.F - y_diff) * (x_diff)
                            +src[c + k] * (y_diff)* (1.F - x_diff)
                            + src[d + k] * (y_diff)* (x_diff));
                    }
                }
            }

            return true;
        }
	}
}

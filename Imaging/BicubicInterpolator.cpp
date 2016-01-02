#pragma once
#include <Imaging/BicubicInterpolator.h>
#include <cassert>

namespace Commons
{
	namespace Imaging
	{
        // Get pixel with border clamping
        inline static uint8_t GetPixel(const uint8_t* src, const ImageInfo& info, int32_t x, int32_t y, uint32_t channel)
        {            
            if (x < 0)
                x = 0;

            if (x >= (int32_t)info.getWidth())
                x = info.getWidth() - 1;

            if (y < 0)
                y = 0;

            if (y >= (int32_t)info.getHeight())
                y = info.getHeight() - 1;


            return src[info.getPixelOffset(x, y) + channel];
        }
        
        bool BicubicInterpolator::interpolateImage(const uint8_t* src, const ImageInfo& srcInfo, uint8_t *dst, const ImageInfo& dstInfo)
        {
            assert(srcInfo.getNumChannels() == dstInfo.getNumChannels());

            const float tx = float(srcInfo.getWidth()) / dstInfo.getWidth();
            const float ty = float(srcInfo.getWidth()) / dstInfo.getHeight();
            const uint32_t srcStride = srcInfo.getScanlineSize();
            const uint32_t dstStride = dstInfo.getScanlineSize();
            const uint32_t numChannels = dstInfo.getNumChannels();

            float C[5] = { 0 };

            for (uint32_t i = 0; i < dstInfo.getHeight(); ++i)
            {
                for (uint32_t j = 0; j < dstInfo.getWidth(); ++j)
                {
                    const int32_t x = int32_t(tx * j);
                    const int32_t y = int32_t(ty * i);
                    const float dx = tx * j - x;
                    const float dy = ty * i - y;

                    for (uint32_t k = 0; k < numChannels; ++k)
                    {
                        for (int32_t jj = 0; jj < 4; ++jj)
                        {
                            // TODO: fixed point
                            const int32_t z = y - 1 + jj;
                            float a0 = GetPixel(src, srcInfo, x, z, k);
                            float d0 = GetPixel(src, srcInfo, x - 1, z, k) - a0;
                            float d2 = GetPixel(src, srcInfo, x + 1, z, k) - a0;
                            float d3 = GetPixel(src, srcInfo, x + 2, z, k) - a0;
                            float a1 = -1.F / 3.F * d0 + d2 - 1.F / 6.F * d3;
                            float a2 = 1.F / 2.F * d0 + 1.F / 2.F * d2;
                            float a3 = -1.F / 6.F * d0 - 1.F / 2.F * d2 + 1.F / 6.F * d3;
                            C[jj] = a0 + a1 * dx + a2 * dx * dx + a3 * dx * dx * dx;

                            d0 = C[0] - C[1];
                            d2 = C[2] - C[1];
                            d3 = C[3] - C[1];
                            a0 = C[1];
                            a1 = -1.F / 3.F * d0 + d2 - 1.F / 6.F * d3;
                            a2 = 1.F / 2.F * d0 + 1.F / 2.F * d2;
                            a3 = -1.F / 6.F * d0 - 1.F / 2.F * d2 + 1.F / 6.F * d3;
                            float value = a0 + a1 * dy + a2 * dy * dy + a3 * dy * dy * dy;

                            if (value > 255.F)
                                value = 255.F;

                            if (value < 0.F)
                                value = 0.F;

                            dst[dstInfo.getPixelOffset(j, i) + k] = (uint8_t)(value);
                        }
                    }
                }
            }

            return true;
        }
	}
}





// TODO: move
static void BicubicInterpolate(const uint8_t *src, int32_t srcWidth, int32_t srcHeight, int32_t numChannels, uint8_t *dst, int32_t dstWidth, int32_t dstHeight)
{
    
}
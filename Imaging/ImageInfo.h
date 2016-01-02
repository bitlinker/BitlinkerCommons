#pragma once
#include <stdint.h>

namespace Commons
{
	namespace Imaging
	{
        class ImageInfo
        {
        public:
            ImageInfo()
                : mWidth(0)
                , mHeight(0)
                , mNumChannels(0)
            {
            }

            ImageInfo(uint32_t width, uint32_t height, uint32_t numChannels)
                : mWidth(width)
                , mHeight(height)
                , mNumChannels(numChannels)
            {
            }

            inline const uint32_t getNumChannels() const { return mNumChannels; }
            inline const uint32_t getWidth() const { return mWidth; }
            inline const uint32_t getHeight() const { return mHeight; }
            inline const uint32_t getScanlineSize() const { return mWidth * mNumChannels; }
            inline const uint32_t getPixelOffset(uint32_t x, uint32_t y) const { return (y * mWidth + x) * mNumChannels; }
            inline const uint32_t getImageSize() const { return getScanlineSize() * mHeight; }

        private:
            uint32_t mWidth;
            uint32_t mHeight;
            uint32_t mNumChannels;
        };
	}
}

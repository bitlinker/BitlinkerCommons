#pragma once
#include <stdint.h>
#include <Streams/IOStream.h>
#include <Imaging/ImageInfo.h>
#include <memory>

namespace Commons
{
	namespace Imaging
	{
        // TODO: implement me...
        class ImageDecoder
        {
        protected:
            ImageDecoder(const IOStream& stream);
        public:

            virtual bool getInfo(ImageInfo& info) = 0;
            virtual bool decode(ImageInfo& info) = 0;

            virtual ~ImageDecoder() {}
        };

        typedef std::shared_ptr<ImageDecoder> ImageDecoderPtr;
	}
}

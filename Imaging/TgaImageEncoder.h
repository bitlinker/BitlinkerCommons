#pragma once
#include <Streams/IOStream.h>
#include <Imaging/ImageInfo.h>

//
// Created by bitlinker on 11.01.2017.
//
namespace Commons
{
    namespace Imaging
    {
        class TgaImageEncoder
        {
        public:
            TgaImageEncoder();
            virtual ~TgaImageEncoder();

            void writeImage(const IOStreamPtr& stream, const ImageInfo& info, const uint8_t* data);
        };
    }
}

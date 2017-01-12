//
// Created by bitlinker on 11.01.2017.
//

#include "TgaImageEncoder.h"

namespace Commons
{
    namespace Imaging
    {
        class TgaHeader
        {
        public:
            uint8_t  idlength;
            uint8_t  colourmaptype;
            uint8_t  datatypecode;
            uint16_t colourmaporigin;
            uint16_t colourmaplength;
            uint8_t  colourmapdepth;
            int16_t x_origin;
            int16_t y_origin;
            uint16_t mWidth;
            uint16_t mHeight;
            uint8_t  mBitsperpixel;
            uint8_t  mImagedescriptor;
        };


        TgaImageEncoder::TgaImageEncoder()
        {
        }

        TgaImageEncoder::~TgaImageEncoder()
        {
        }

        void TgaImageEncoder::writeImage(const IOStreamPtr& stream, const ImageInfo& info, const uint8_t* data)
        {
            TgaHeader header;
            header.datatypecode = 2;
            header.mWidth = info.getWidth();
            header.mHeight = info.getHeight();
            header.mBitsperpixel = info.getNumChannels() * 8;

            stream->write(&header, sizeof(TgaHeader));

            const uint8_t* src = data;
            for (uint32_t i = 0; i < info.getHeight(); ++i)
            {
                stream->write(src, info.getWidth() * info.getNumChannels());
                src += info.getScanlineSize();
            }

//            putc(0, fTile);
//            putc(0, fTile);
//            putc(2, fTile);                         /* uncompressed RGB */
//            putc(0, fTile); putc(0, fTile);
//            putc(0, fTile); putc(0, fTile);
//            putc(0, fTile);
//            putc(0, fTile); putc(0, fTile);           /* X origin */
//            putc(0, fTile); putc(0, fTile);           /* y origin */
//            putc((mWidth & 0x00FF), fTile);
//            putc((mWidth & 0xFF00) / 256, fTile);
//            putc((mHeight & 0x00FF), fTile);
//            putc((mHeight & 0xFF00) / 256, fTile);
//            putc(32, fTile);                        /* 32 bit bitmap */
//            putc(0, fTile);
//
//            fwrite(data, mWidth * mHeight * 4, 1, fTile);
        }

    }
}
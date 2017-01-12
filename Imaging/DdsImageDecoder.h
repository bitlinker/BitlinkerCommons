#pragma once
// TODO: implement me...
//
//
//
//class Pixelmap
//{
//public:
//    //static const char FORMAT_RGBA[4] = { 0x15, 0x0, 0x0, 0x0 };
//
//    struct Header
//    {
//        uint16_t mMagic; // 00 02
//        uint16_t mWidth;
//        uint16_t mHeight;
//        uint16_t mMipMaps;  // ? 8, 10
//        uint16_t mU1;       // ? 8
//        uint16_t mU2;
//        char mFormat[4];
//    };
//
//public:
//    Header mHeader;
//};
//
//class DXTDecoder
//{
//public:
//    class DXT1Block
//    {
//    public:
//        uint16_t mColor[2];
//        uint32_t mBits;
//    };
//
//    uint32_t rgb565to888(uint16_t value)
//    {
//        uint8_t r = ((((value >> 11) & 0x1F) * 527) + 23) >> 6;
//        uint8_t g = ((((value >> 5) & 0x3F) * 259) + 33) >> 6;
//        uint8_t b = (((value & 0x1F) * 527) + 23) >> 6;
//        // R8 = (int) floor( R5 * 255.0 / 31.0 + 0.5);
//        // G8 = (int) floor( G6 * 255.0 / 63.0 + 0.5);
//        // B8 = (int) floor( R5 * 255.0 / 31.0 + 0.5);
//        uint32_t result = (b << 16 | g << 8 | r) | 0xFF000000; // TODO: alpha
//        return result;
//    }
//
//    uint32_t lerpColors(uint32_t c1, uint32_t c2, uint32_t value, uint32_t divisor)
//    {
//        uint32_t result = 0;
//        uint8_t* cc1 = reinterpret_cast<uint8_t*>(&c1);
//        uint8_t* cc2 = reinterpret_cast<uint8_t*>(&c2);
//        uint8_t* out = reinterpret_cast<uint8_t*>(&result);
//        for (uint32_t i = 0; i < 4; ++i) // TODO: BPP
//        {            
//            *out++ = (*cc1++ * value + *cc2++ * (divisor - value)) / divisor;
//        }
//        return result;
//    }
//
//    void decodeDXT1Block()
//    {
//        // TODO
//    }
//
//    void decodeDXT1(const uint8_t* src, const uint32_t width, const uint32_t height, uint8_t* dst)
//    {
//        const uint32_t BLOCK_SIZE = 4;
//        const uint32_t BPP = 4;
//
//        uint32_t numBlocksX = (width + 3) / 4;
//        uint32_t numBlocksY = (height + 3) / 4;
//
//        // TODO: endianess?
//        for (int blockY = 0; blockY < numBlocksY; ++blockY)
//        {
//            for (int blockX = 0; blockX < numBlocksX; ++blockX)
//            {
//                const DXT1Block* blockPtr = reinterpret_cast<const DXT1Block*>(src + (blockX + blockY * numBlocksX) * sizeof(DXT1Block));
//
//                bool isColor0Greater = blockPtr->mColor[0] > blockPtr->mColor[1];
//
//                // TODO: in block class decoding
//                uint32_t c[2];
//                for (int i = 0; i < 2; ++i)
//                {
//                    c[i] = rgb565to888(blockPtr->mColor[i]);
//                }
//
//
//                uint8_t* dstBlockPtr = dst + blockX * BLOCK_SIZE * BPP + blockY * BLOCK_SIZE * width * BPP;
//                for (uint32_t y = 0; y < 4; ++y)
//                {
//                    uint32_t* dstPixPtr = reinterpret_cast<uint32_t*>(dstBlockPtr + y * width * BPP);
//                    for (uint32_t x = 0; x < 4; ++x)
//                    {
//                        uint32_t code = (blockPtr->mBits >> 2 * (4 * y + x)) & 0x03;
//                        switch (code)
//                        {
//                        case 0:
//                            *dstPixPtr = c[0];
//                            break;
//                        case 1:
//                            *dstPixPtr = c[1];
//                            break;
//                        case 2:
//                            *dstPixPtr = isColor0Greater ?
//                                lerpColors(c[0], c[1], 2, 3) :
//                                lerpColors(c[0], c[1], 1, 2);
//                            break;
//                        case 3:
//                            *dstPixPtr = isColor0Greater ?
//                                lerpColors(c[0], c[1], 1, 3) :
//                                //0xFF000000; // TODO: dxt1_extra sets alpha here...
//                                0x00000000; // TODO: dxt1_extra sets alpha here...
//                            break;
//                        }
//                        ++dstPixPtr;                        
//                    }
//                }
//            }
//        }
//    }
//};
//
//class DDSFile
//{
//public:
//    static const uint32_t DDS_MAGIC = 0x20534444;
//
//    static const uint32_t DDS_PF_DXT1 = 0x31545844;
//
//    static const uint32_t DDS_FLAG_CAPS = 0x1;
//    static const uint32_t DDS_FLAG_HEIGHT = 0x2;
//    static const uint32_t DDS_FLAG_WIDTH = 0x4;
//    static const uint32_t DDS_FLAG_PITCH = 0x8;
//    static const uint32_t DDS_FLAG_PIXELFORMAT = 0x1000;
//    static const uint32_t DDS_FLAG_MIPCOUNT = 0x20000;
//    static const uint32_t DDS_FLAG_LINEARSIZE = 0x80000;
//    static const uint32_t DDS_FLAG_DEPTH = 0x800000;
//
//    static const uint32_t DDS_CAPS_COMPLEX = 0x8;
//    static const uint32_t DDS_CAPS_MIPMAPS = 0x400000;
//    static const uint32_t DDS_CAPS_TEXTURE = 0x1000;
//
//    // TODO: caps2 (cubemap)
//
//    class PixelFormat
//    {
//    public:
//        uint32_t dwSize;
//        uint32_t dwFlags;
//        uint32_t dwFourCC;
//        uint32_t dwRGBBitCount;
//        uint32_t dwRBitMask;
//        uint32_t dwGBitMask;
//        uint32_t dwBBitMask;
//        uint32_t dwABitMask;
//    };
//
//    class Header
//    {
//    public:
//        uint32_t        dwSize;
//        uint32_t        dwFlags;
//        uint32_t        dwHeight;
//        uint32_t        dwWidth;
//        uint32_t        dwPitchOrLinearSize;
//        uint32_t        dwDepth;
//        uint32_t        dwMipMapCount;
//        uint32_t        dwReserved1[11];
//        PixelFormat     ddspf;
//        uint32_t        dwCaps;
//        uint32_t        dwCaps2;
//        uint32_t        dwCaps3;
//        uint32_t        dwCaps4;
//        uint32_t        dwReserved2;
//    };
//
//    class Header_DXT10
//    {
//    public:
//        uint32_t        dxgiFormat;
//        uint32_t        resourceDimension;
//        uint32_t        miscFlag;
//        uint32_t        arraySize;
//        uint32_t        miscFlags2;
//    };
//
//    explicit DDSFile(IOStreamPtr& stream)
//    {
//        stream->read(&mMagic, sizeof(mMagic));
//        if (DDS_MAGIC != mMagic)
//        {
//            throw Commons::SerializationException("Unknown magic"); // TODO: output magic
//        }
//
//        stream->read(&mHeader, sizeof(mHeader));
//
//        // TODO: parse DXT10 header
//        if (sizeof(mHeader) != mHeader.dwSize)
//        {
//            throw Commons::SerializationException("Wrong DXT header size"); // TODO: output magic
//        }
//
//        if (mHeader.dwFlags & DDS_FLAG_PIXELFORMAT) // TODO: assert it 
//        {
//            if (sizeof(mHeader.ddspf) != mHeader.ddspf.dwSize)
//            {
//                throw Commons::SerializationException("Wrong DXT pixelformat size"); // TODO: output magic
//            }
//
//            // TODO: check flags
//            if (mHeader.ddspf.dwFourCC == DDS_PF_DXT1)
//            {
//                // TODO: decode DXT1
//                int k = 0;
//                std::vector<uint8_t> data(mHeader.dwPitchOrLinearSize);
//                stream->read(&data[0], mHeader.dwPitchOrLinearSize);
//
//                DXTDecoder decoder;
//
//                uint32_t dstSize = mHeader.dwWidth * mHeader.dwHeight * 4;
//                std::vector<uint8_t> dst(dstSize);
//                decoder.decodeDXT1(&data[0], mHeader.dwWidth, mHeader.dwHeight, &dst[0]);
//                FileStream out("d:/!github_cmake/carma-vs/Debug/reincarnation/outdxt.data", FileStream::MODE_WRITE);
//                out.write(&dst[0], dstSize);
//
//            }
//        }
//
//
//    }
//
//public:
//    uint32_t mMagic;
//    Header mHeader;
//
//    //For block - compressed formats, compute the pitch as :
//    //max(1, ((width + 3) / 4)) * block - size
//    //    The block - size is 8 bytes for DXT1, BC1, and BC4 formats, and 16 bytes for other block - compressed formats.
//    //    For R8G8_B8G8, G8R8_G8B8, legacy UYVY - packed, and legacy YUY2 - packed formats, compute the pitch as :
//    //((width + 1) >> 1) * 4
//    //    For other formats, compute the pitch as :
//    //(width * bits - per - pixel + 7) / 8
//    //    You divide by 8 for byte alignment.
//};
//
//int main()
//{
//    IOStreamPtr strm(new FileStream("d:/!github_cmake/carma-vs/Debug/reincarnation/dxt1.dds", FileStream::MODE_READ));
//    DDSFile dds(strm);
//
//   /* FileStream strm("d:/!github_cmake/carma-vs/Debug/reincarnation/normal.tdx", FileStream::MODE_READ);
//
//    Pixelmap pix;
//
//    strm.read(&pix.mHeader, sizeof(Pixelmap::Header));
//
//    DXTDecoder decoder;
//
//    uint16_t width = pix.mHeader.mWidth;
//    uint16_t height = pix.mHeader.mHeight;
//    for (uint32_t mipMap = 0; width > 0 && height > 0; ++mipMap)
//    {
//        std::stringstream ss;
//        ss << "d:/!github_cmake/carma-vs/Debug/reincarnation/out" << mipMap << ".data";
//        FileStream out(ss.str(), FileStream::MODE_WRITE);
//
//        uint32_t size = width * height * 4 / 8;
//        if (size == 0)
//            break;
//
//        std::vector<uint8_t> level(size);
//        strm.read(&level[0], size);
//
//        uint32_t dstSize = width * height * 4;
//        std::vector<uint8_t> dst(dstSize);
//        decoder.decodeDXT1(&level[0], width, height, &dst[0]);
//        out.write(&dst[0], dstSize);
//
//        width >>= 1;
//        height >>= 1;
//
//        if (width == 0 || height == 0)
//            break;
//
//        uint32_t pos = strm.tell();
//        std::cout << "Mip " << mipMap << ", " << width << "x" << height << " at: " << pos << std::endl;
//    }
//*/
//    // Last level is single point
//
//
//    return 0;
//}
//
//
//
//

#include <Common/Endianness.h>

namespace Commons
{
    EndiannessType Endianness::getCpuEndianness()
    {
        short int word = 0x0001;
        char *byte = (char *)&word;
        return (byte[0] == 0) ? BIG_ENDIAN : LITTLE_ENDIAN;
    }

    uint16_t Endianness::ByteSwapUInt16(uint16_t source)
    {
        return ((source & 0xff) << 8) | ((source & 0xff00) >> 8);
    }

    uint32_t Endianness::ByteSwapUInt32(uint32_t source)
    {
        source = (source & 0x0000FFFF) << 16 | (source & 0xFFFF0000) >> 16;
        source = (source & 0x00FF00FF) << 8 | (source & 0xFF00FF00) >> 8;
        return source;
    }    
}
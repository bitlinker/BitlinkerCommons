#include <Common/Endianness.h>

namespace Commons
{
	Endianness::EndiannessType Endianness::GetCpuEndianness()
    {
        short int word = 0x0001;
        char *byte = (char *)&word;
        return (byte[0] == 0) ? BIG_ENDIAN : LITTLE_ENDIAN;
    }

    bool Endianness::NeedSwap(EndiannessType target)
    {
        return GetCpuEndianness() != target;
    }

    void Endianness::Swap16(void* src)
    {
        uint16_t* source = reinterpret_cast<uint16_t*>(src);
        *source = ((*source & 0xff) << 8) | ((*source & 0xff00) >> 8);
    }

    void Endianness::Swap32(void* src)
    {
        uint32_t* source = reinterpret_cast<uint32_t*>(src);
        *source = (*source & 0x0000FFFF) << 16 | (*source & 0xFFFF0000) >> 16;
        *source = (*source & 0x00FF00FF) << 8 | (*source & 0xFF00FF00) >> 8;
    }    
}
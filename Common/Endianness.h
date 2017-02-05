#pragma once
#include <Common/NonObject.h>
#include <stdint.h>

namespace Commons
{    
    class Endianness : public NonObject
    {
    public:
        enum EndiannessType
        {
            LITTLE_ENDIAN,
            BIG_ENDIAN
        };

        static EndiannessType GetCpuEndianness();
        static bool NeedSwap(EndiannessType target);

        static void Swap16(void* src);
        static void Swap32(void* src);
    };
}

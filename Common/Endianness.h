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

        static EndiannessType getCpuEndianness();

        static uint16_t ByteSwapUInt16(uint16_t source);
        static uint32_t ByteSwapUInt32(uint32_t source);
    };
}

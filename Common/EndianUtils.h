#pragma once
#include <Common/NonObject.h>
#include <stdint.h>

namespace Commons
{    
    class EndianUtils : public NonObject
    {
    public:
        static bool IsArchBigEndian();

        static uint16_t ByteSwapUInt16(uint16_t source);
        static uint32_t ByteSwapUInt32(uint32_t source);
    };
}

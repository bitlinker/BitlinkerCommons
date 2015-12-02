#pragma once
#include <Common/NonObject.h>
#include <stdint.h>
#include <string>

namespace Commons
{    
    class StringUtils : public NonObject
    {
    public:
        static const std::string FormatString(const char* fmt, ...);
    };
}

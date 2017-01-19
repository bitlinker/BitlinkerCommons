#include <Common/StringUtils.h>
#include <stdio.h>
#include <stdarg.h>

namespace Commons
{    
    //// TODO: for linux/mac
    //static int _vscprintf(const char * format, va_list pargs)
    //{
    //    int retval;
    //    va_list argcopy;
    //    va_copy(argcopy, pargs);
    //    retval = vsnprintf(NULL, 0, format, argcopy);
    //    va_end(argcopy);
    //    return retval;
    //}

    const std::string StringUtils::FormatString(const char* fmt, ...)
    {        
        va_list args;
        va_start(args, fmt);
        uint32_t len = ::_vscprintf(fmt, args);
        std::string result;
        result.resize(len);
        ::vsprintf(&result[0], fmt, args);
        va_end(args);
        return result;
    }    
}

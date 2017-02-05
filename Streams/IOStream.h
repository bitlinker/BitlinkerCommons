#pragma once
#include <memory>
#include <Common/NonCopyable.h>

namespace Commons
{
    class IOStream : public NonCopyable
    {
    public:
        enum Origin
        {
            ORIGIN_SET,
            ORIGIN_CUR,
            ORIGIN_END,
        };

        typedef uint32_t size_type;
        typedef int32_t offset_type;

    public:
        virtual ~IOStream() {};

        virtual size_type write(const void* data, size_type size) = 0;
        virtual size_type read(void* data, size_type size) = 0;
        virtual size_type tell() = 0;
        virtual size_type size() = 0;
        virtual bool isEOF() = 0;
        virtual void seek(offset_type offset, Origin origin) = 0;
        virtual void flush() = 0;
    };

    typedef std::shared_ptr<IOStream> IOStreamPtr;
}
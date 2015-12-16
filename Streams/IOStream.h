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

    public:
        virtual ~IOStream() {};

        virtual void write(const void* data, uint32_t size) = 0;
        virtual void read(void* data, uint32_t size) = 0;
        virtual uint32_t tell() = 0;
        virtual uint32_t size() = 0;
        virtual bool isEOF() = 0;
        virtual void seek(int32_t offset, Origin origin) = 0;
    };

    typedef std::shared_ptr<IOStream> IOStreamPtr;
}
#pragma once
#include <Streams/IOStream.h>
#include <cstdio>
#include <string>
#include <stdint.h> 
#include <memory>


namespace Commons
{
    class FileStream : public IOStream
    {
    public:
        enum Mode
        {
            MODE_READ,
            MODE_WRITE,
        };

    public:
        FileStream(const std::string& fileName, Mode mode);
        virtual ~FileStream();

        virtual size_type write(const void* data, size_type size);
        virtual size_type read(void* data, size_type size);
        virtual size_type tell();
        virtual size_type size();
        virtual bool isEOF();
        virtual void seek(offset_type offset, Origin origin);

    private:
        FILE* mF;
    };

    typedef std::shared_ptr<FileStream> FileStreamPtr;
}
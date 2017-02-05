#pragma once
#include <Streams/IOStream.h>
#include <vector>
#include <memory>

namespace Commons
{
    class MemoryStream : public IOStream
    {
    public:
        MemoryStream(uint8_t* buffer, size_type size);
        MemoryStream(size_type size);
        virtual ~MemoryStream();

        void* getPtr() const { return mPtr; }
        const void* getConstPtr() const { return mPtr; }
        void* getCurPtr() const { return mPtr + mPos; }
        const void* getCurConstPtr() const { return mPtr + mPos; }

        virtual size_type write(const void* data, size_type size);
        virtual size_type read(void* data, size_type size);
        virtual size_type tell();
        virtual size_type size();
        virtual bool isEOF();
        virtual void seek(offset_type offset, Origin origin);
        virtual void flush() {};

    private:
        void seekSet(offset_type offset);
        void seekCur(offset_type offset);
        void seekEnd(offset_type offset);

    private:
        std::vector<uint8_t> mBuffer;
        uint8_t* mPtr;
        bool mIsExternPtr;
        size_type mSize;
        size_type mPos;
    };

    typedef std::shared_ptr<MemoryStream> MemoryStreamPtr;
}
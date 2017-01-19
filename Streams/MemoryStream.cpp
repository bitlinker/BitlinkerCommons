#include <Common/StringUtils.h>
#include <Streams/MemoryStream.h>
#include <Exception/Exception.h>
#include <memory.h>
#include <algorithm>

namespace Commons
{
    MemoryStream::MemoryStream(uint8_t* buffer, size_type size)
    : mBuffer()
    , mPtr(buffer)
    , mIsExternPtr(true)
    , mSize(size)
    , mPos(0)
    {
    }

    MemoryStream::MemoryStream(size_type size)
    : mBuffer(size)
    , mPtr(&mBuffer[0])
    , mIsExternPtr(false)
    , mSize(size)
    , mPos(0)
    {
    }

    MemoryStream::~MemoryStream()
    {
    }

    IOStream::size_type MemoryStream::write(const void* data, size_type size)
    {
        if (mPos > mSize) return 0;

        size_type realSize = std::min(size, mSize - mPos);
        if (realSize > 0)
        {
            ::memcpy(static_cast<uint8_t*>(mPtr) + mPos, data, realSize);
            mPos += realSize;
        }
        return realSize;
    }

    IOStream::size_type MemoryStream::read(void* data, size_type size)
    {
        if (mPos > mSize) return 0;

        size_type realSize = std::min(size, mSize - mPos);
        if (realSize > 0)
        {
            ::memcpy(data, static_cast<uint8_t*>(mPtr) + mPos, realSize);
            mPos += realSize;
        }
        return realSize;
    }

    IOStream::size_type MemoryStream::tell()
    {
        return mPos;
    }

    IOStream::size_type MemoryStream::size()
    {
        return mSize;
    }

    bool MemoryStream::isEOF()
    {
        return mPos >= mSize;
    }

    void MemoryStream::seekSet(offset_type offset)
    {
        if (offset >= 0 && static_cast<size_type>(offset) < mSize)
            mPos = offset;
        else
            throw IOException("Seek beyond buffer size");
    }

    void MemoryStream::seekCur(offset_type offset)
    {
        if ((offset >= 0 && static_cast<uint32_t>(offset) + mPos < mSize) ||
            (offset < 0 && static_cast<uint32_t>(-offset) < mSize - mPos))
        {
            mPos += offset;
        }
        else
            throw IOException("Seek beyond buffer size or start");
    }

    void MemoryStream::seekEnd(offset_type offset)
    {
        if (offset <= 0 && static_cast<uint32_t>(-offset) < mSize)
        {
            mPos = mSize - offset;
        }
        else
            throw IOException("Seek below buffer size");
    }

    //throw IOException("Seek failed");

    void MemoryStream::seek(offset_type offset, Origin origin)
    {
        switch (origin)
        {
        case IOStream::ORIGIN_SET: seekSet(offset); break;
        case IOStream::ORIGIN_CUR: seekCur(offset); break;           
        case IOStream::ORIGIN_END: seekEnd(offset); break;
        default: throw IOException(StringUtils::FormatString("Unknown seek origin: %d", origin));
        }
    }
}
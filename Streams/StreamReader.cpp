#include <Common/StringUtils.h>
#include <Streams/StreamReader.h>
#include <Exception/Exception.h>
#include <cassert>

namespace Commons {
    StreamReader::StreamReader(const IOStreamPtr& stream, Endianness::EndiannessType endianness)
        : mStream(stream)
    {
        assert(stream);
        mNeedSwap = Endianness::NeedSwap(endianness);
    }

    StreamReader::~StreamReader()
    {
    }

    // TODO:
    // BufferedInputStream
    // TextInputStream

    void StreamReader::read(void* data, IOStream::size_type size)
    {
        if (mStream->read(data, size) != size)
            throw IOException(StringUtils::FormatString("IO Error at %d", mStream->tell()));
    }

    IOStream::size_type StreamReader::tell()
    {
        return mStream->tell();
    }

    IOStream::size_type StreamReader::size()
    {
        return mStream->size();
    }

    bool StreamReader::isEOF()
    {
        return mStream->isEOF();
    }

    void StreamReader::seek(IOStream::offset_type offset, IOStream::Origin origin)
    {
        mStream->seek(offset, origin);
    }

    template<typename T>
    void StreamReader::readChecked(T& value)
    {
        if (mStream->read(&value, sizeof(value)) != sizeof(value))
        {
            if (mStream->isEOF())
                throw EOFException(StringUtils::FormatString("Stream reached EOF at %d", mStream->tell()));
            else
                throw IOException(StringUtils::FormatString("IO Error at %d", mStream->tell()));
        }
    }

    uint32_t StreamReader::readUInt32() 
    {
        uint32_t origVal;
        readChecked(origVal);
        if (mNeedSwap) Endianness::Swap32(&origVal);
        return origVal;
    }

    uint16_t StreamReader::readUInt16() 
    {
        uint16_t origVal;
        readChecked(origVal);
        if (mNeedSwap) Endianness::Swap16(&origVal);
        return origVal;
    }

    uint8_t StreamReader::readUInt8() 
    {
        uint8_t value;
        readChecked(value);
        return value;
    }

    float StreamReader::readFloat()
    {
        float origVal;
        readChecked(origVal);
        if (mNeedSwap) Endianness::Swap32(&origVal);
        return origVal;
    }

    std::string StreamReader::readNullTermString(uint32_t reserveBuf) 
    {
        std::string res;
        res.reserve(reserveBuf);
        char ch = 0;
        while (true) 
        {
            readChecked(ch);
            if (ch == '\0')
                break;
            res.push_back(ch);
        }
        return res;
    }
 }
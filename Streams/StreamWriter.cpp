#include <Streams/StreamWriter.h>
#include <Common/StringUtils.h>
#include <Streams/StreamReader.h>
#include <Exception/Exception.h>
#include <cassert>

namespace Commons
{
    StreamWriter::StreamWriter(const IOStreamPtr& stream, Endianness::EndiannessType endianness)
        : mStream(stream)
    {
        assert(stream);
        mNeedSwap = Endianness::NeedSwap(endianness);
    }

    StreamWriter::~StreamWriter()
    {
    }

    void StreamWriter::write(const void* data, IOStream::size_type size)
    {
        if (mStream->write(data, size) != size)
            throw IOException(StringUtils::FormatString("IO Error at %d", mStream->tell()));
    }

    IOStream::size_type StreamWriter::tell()
    {
        return mStream->tell();
    }

    bool StreamWriter::isEOF()
    {
        return mStream->isEOF();
    }

    void StreamWriter::seek(IOStream::offset_type offset, IOStream::Origin origin)
    {
        return mStream->seek(offset, origin);
    }

    void StreamWriter::flush()
    {
        mStream->flush();
    }

    void StreamWriter::writeUInt32(uint32_t value)
    {
        if (mNeedSwap) Endianness::Swap32(&value);
        writeChecked(value);        
    }

    void StreamWriter::writeUInt16(uint16_t value)
    {
        if (mNeedSwap) Endianness::Swap16(&value);
        writeChecked(value);
    }

    void StreamWriter::writeUInt8(uint8_t value)
    {
        writeChecked(value);
    }

    void StreamWriter::writeFloat(float value)
    {
        if (mNeedSwap) Endianness::Swap32(&value);
        writeChecked(value);
    }

    void StreamWriter::writeNullTermString(const std::string& value)
    {
        if (value.empty()) return;

        if (mStream->write(&value[0], value.size() + 1) != value.size() + 1)
            throw IOException(StringUtils::FormatString("IO Error at %d", mStream->tell()));
    }

    template<typename T>
    void StreamWriter::writeChecked(T& value)
    {
        if (mStream->write(&value, sizeof(value)) != sizeof(value))
        {
            if (mStream->isEOF())
                throw EOFException(StringUtils::FormatString("Stream reached EOF at %d", mStream->tell()));
            else
                throw IOException(StringUtils::FormatString("IO Error at %d", mStream->tell()));
        }
    }
}
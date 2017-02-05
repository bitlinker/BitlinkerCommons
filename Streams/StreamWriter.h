#pragma once
#include <Streams/IOStream.h>
#include <Common/Endianness.h>
#include <iostream>

namespace Commons
{
    class StreamWriter
    {
    public:
        StreamWriter(const IOStreamPtr& stream, Endianness::EndiannessType endianness);
        ~StreamWriter();

        void write(const void* data, IOStream::size_type size);
        IOStream::size_type tell();
        bool isEOF();
        void seek(IOStream::offset_type offset, IOStream::Origin origin);
        void flush();

        void writeUInt32(uint32_t value);
        void writeUInt16(uint16_t value);
        void writeUInt8(uint8_t value);
        void writeFloat(float value);
        void writeNullTermString(const std::string& value);

        bool needSwap() const { return mNeedSwap; }

    private:
        template<typename T>
        void writeChecked(T& value);

    private:
        IOStreamPtr mStream;
        bool mNeedSwap;
    };
}
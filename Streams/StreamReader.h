#pragma once
#include <Streams/IOStream.h>
#include <Common/Endianness.h>
#include <iostream>

namespace Commons
{
    class StreamReader
    {
    public:
        StreamReader(const IOStreamPtr& stream, Endianness::EndiannessType endianness);
        ~StreamReader();

        void read(void* data, IOStream::size_type size);
        IOStream::size_type tell();
        IOStream::size_type size();
        bool isEOF();
        void seek(IOStream::offset_type offset, IOStream::Origin origin);
            
        uint32_t readUInt32();
        uint16_t readUInt16();
        uint8_t readUInt8();
        float readFloat();
        std::string readNullTermString(uint32_t reserveBuf = 256);

        bool needSwap() const { return mNeedSwap; }

    private:
        template<typename T>
        void readChecked(T& value);

    private:
        IOStreamPtr mStream;
        bool mNeedSwap;
    };
}

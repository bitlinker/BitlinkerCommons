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

        void* getPtr() const { return m_Ptr; }
        const void* getConstPtr() const { return m_Ptr; }
        void* getCurPtr() const { return m_Ptr + m_pos; }
        const void* getCurConstPtr() const { return m_Ptr + m_pos; }

        virtual void write(const void* data, size_type size);
        virtual void read(void* data, size_type size);
        virtual size_type tell();
        virtual size_type size();
        virtual bool isEOF();
        virtual void seek(offset_type offset, Origin origin);

    private:
        std::vector<uint8_t> m_buffer;
        uint8_t* m_Ptr;
        bool m_isExternPtr;
        size_type m_size;
        size_type m_pos;
    };

    typedef std::shared_ptr<MemoryStream> MemoryStreamPtr;
}
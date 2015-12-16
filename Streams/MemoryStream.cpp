#include <Streams/MemoryStream.h>
#include <iostream>

namespace Commons
{
    MemoryStream::MemoryStream(uint8_t* buffer, uint32_t size)
    : m_buffer()
    , m_Ptr(buffer)
    , m_isExternPtr(true)
    , m_size(size)
    , m_pos(0)
    {
    }

    MemoryStream::MemoryStream(uint32_t size)
    : m_buffer(size)
    , m_Ptr(&m_buffer[0])
    , m_isExternPtr(false)
    , m_size(size)
    , m_pos(0)
    {
    }

    MemoryStream::~MemoryStream()
    {
    }

    void MemoryStream::write(const void* data, uint32_t size)
    {
        if (m_pos + size <= m_size)
        {
            ::memcpy(static_cast<uint8_t*>(m_Ptr) + m_pos, data, size);
            m_pos += size;
        }
        else
        {
            throw std::ios_base::failure("writing out of buffer bounds");
        }
    }

    void MemoryStream::read(void* data, uint32_t size)
    {
        if (m_pos + size <= m_size)
        {
            ::memcpy(data, static_cast<uint8_t*>(m_Ptr) + m_pos, size);
            m_pos += size;
        }
        else
        {
            throw std::ios_base::failure("reading out of buffer bounds");
        }
    }

    uint32_t MemoryStream::tell()
    {
        return m_pos;
    }

    uint32_t MemoryStream::size()
    {
        return m_size;
    }

    bool MemoryStream::isEOF()
    {
        return m_pos >= m_size;
    }

    void MemoryStream::seek(int32_t offset, Origin origin)
    {
        bool result = true;
        switch (origin)
        {
        case IOStream::ORIGIN_SET:
            if (offset >= 0 && static_cast<uint32_t>(offset) < m_size)
                m_pos = offset;
            else
                result = false;
            break;
        case IOStream::ORIGIN_CUR:
            if ((offset >= 0 && static_cast<uint32_t>(offset) + m_pos < m_size) ||
                (offset < 0 && static_cast<uint32_t>(-offset) < m_size - m_pos))
            {
                m_pos += offset;
            }
            else
                result = false;
            break;
        case IOStream::ORIGIN_END:
            if (offset <= 0 && static_cast<uint32_t>(-offset) < m_size)
            {
                m_pos = m_size - offset;
            }
            else
                result = false;
            break;
        default:
            result = false;
        }

        if (!result)
            throw std::ios_base::failure("seek failed");
    }
}
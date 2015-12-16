#include <Streams/FileStream.h>
#include <Exception/Exception.h>
#include <Common/StringUtils.h>

namespace Commons
{
    static const char* TranslateMode(FileStream::Mode mode)
    {
        switch (mode)
        {
        case FileStream::MODE_READ:
            return "rb";
        case FileStream::MODE_WRITE:
            return "wb";
        }
        return "";
    }

    static int TranslateOrigin(FileStream::Origin origin)
    {
        switch (origin)
        {
        case FileStream::ORIGIN_CUR:
            return SEEK_CUR;
        case FileStream::ORIGIN_END:
            return SEEK_END;
        case FileStream::ORIGIN_SET:
        default:
            return SEEK_SET;
        }
    }

    FileStream::FileStream(const std::string& fileName, Mode mode)
    : m_f(nullptr)
    {
        if (::fopen_s(&m_f, fileName.c_str(), TranslateMode(mode)) != 0)
        {
            throw IOException(StringUtils::FormatString("Can't open file %s", fileName.data()));
        }
    }

    FileStream::~FileStream()
    {
        ::fclose(m_f);
        m_f = nullptr;
    }

    void FileStream::write(const void* data, uint32_t size)
    {
        if (::fwrite(data, size, 1, m_f) != 1)
        {
            throw IOException("write failed");
        }
    }

    void FileStream::read(void* data, uint32_t size)
    {
        if (::fread(data, size, 1, m_f) != 1)
        {
            throw IOException("read failed");
        }
    }

    uint32_t FileStream::tell()
    {
        return ftell(m_f);
    }

    uint32_t FileStream::size()
    {
        uint32_t curPos = tell();
        seek(0, ORIGIN_END);
        uint32_t result = tell();
        seek(curPos, ORIGIN_SET);
        return result;
    }

    bool FileStream::isEOF()
    {
        return (::feof(m_f) != 0);
    }

    void FileStream::seek(int32_t offset, Origin origin)
    {
        if (::fseek(m_f, offset, TranslateOrigin(origin)) != 0)
        {
            throw IOException("seek failed");
        }
    }
}
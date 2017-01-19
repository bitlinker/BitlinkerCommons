#include <Streams/FileStream.h>
#include <Exception/Exception.h>
#include <Common/StringUtils.h>

namespace Commons
{
    static const char* TranslateMode(FileStream::Mode mode)
    {
        switch (mode)
        {
        case FileStream::MODE_READ: return "rb";
        case FileStream::MODE_WRITE: return "wb";
        }
        throw IOException(StringUtils::FormatString("Unknown file mode: %d", mode));
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
    : mF(nullptr)
    {
        if ((mF = ::fopen(fileName.c_str(), TranslateMode(mode))) == 0)
        {
            throw IOException(StringUtils::FormatString("Can't open file %s", fileName.data()));
        }
    }

    FileStream::~FileStream()
    {
        ::fclose(mF);
        mF = nullptr;
    }

    IOStream::size_type FileStream::write(const void* data, size_type size)
    {
        return ::fwrite(data, 1, size, mF);
    }

    IOStream::size_type FileStream::read(void* data, size_type size)
    {
        return ::fread(data, 1, size, mF);        
    }

    IOStream::size_type FileStream::tell()
    {
        return ::ftell(mF);
    }

    IOStream::size_type FileStream::size()
    {
        size_type curPos = tell();
        seek(0, ORIGIN_END);
        size_type result = tell();
        seek(curPos, ORIGIN_SET);
        return result;
    }

    bool FileStream::isEOF()
    {
        return (::feof(mF) != 0);
    }

    void FileStream::seek(offset_type offset, Origin origin)
    {
        if (::fseek(mF, offset, TranslateOrigin(origin)) != 0)
        {
            throw IOException("Seek failed");
        }
    }
}
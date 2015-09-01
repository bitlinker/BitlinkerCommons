#pragma once
#include "IOStream.h"
#include <cstdio>
#include <string>
#include <stdint.h> 
#include <memory>

class FileStream : public IOStream
{
public:
	enum Mode
	{
		MODE_READ,
		MODE_WRITE,
	};

public:
	FileStream(const std::string& fileName, Mode mode);
	virtual ~FileStream();

	virtual void write(const void* data, uint32_t size);
	virtual void read(void* data, uint32_t size);
	virtual uint32_t tell();
	virtual uint32_t size();
	virtual bool isEOF();
	virtual void seek(int32_t offset, Origin origin);

private:
	FILE* m_f;
};

typedef std::shared_ptr<FileStream> FileStreamPtr;
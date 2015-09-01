#pragma once
#include "IOStream.h"
#include <vector>
#include <memory>

class MemoryStream : public IOStream
{
public:
	MemoryStream(uint8_t* buffer, uint32_t size);
	MemoryStream(uint32_t size);
	virtual ~MemoryStream();

	void* getPtr() const { return m_Ptr; }
	const void* getConstPtr() const { return m_Ptr; }

	virtual void write(const void* data, uint32_t size);
	virtual void read(void* data, uint32_t size);
	virtual uint32_t tell();
	virtual uint32_t size();
	virtual bool isEOF();
	virtual void seek(int32_t offset, Origin origin);

private:
	std::vector<uint8_t> m_buffer;
	void* m_Ptr;
	bool m_isExternPtr;
	uint32_t m_size;
	uint32_t m_pos;
};

typedef std::shared_ptr<MemoryStream> MemoryStreamPtr;

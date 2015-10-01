#pragma once
#include <Common.h>

namespace Commons
{
	class Exception : public std::runtime_error
	{
	public:
		explicit Exception(const std::string& what)
			: std::runtime_error(what)
		{
		}
	};

	class UnknownException : public Exception
	{
	public:
		explicit UnknownException(const std::string& what)
			: Exception(what)
		{
		}
	};

	class IOException : public Exception
	{
	public:
		explicit IOException(const std::string& what)
			: Exception(what)
		{
		}
	};

	class EOFException : public IOException
	{
	public:
		explicit EOFException(const std::string& what)
			: IOException(what)
		{
		}
	};

	class SerializationException : public Exception
	{
	public:
		explicit SerializationException(const std::string& what)
			: Exception(what)
		{
		}
	};

	class GLException : public Exception
	{
	public:
		explicit GLException(const std::string& what)
			: Exception(what)
		{
		}
	};
}

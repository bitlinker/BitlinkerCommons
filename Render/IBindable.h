#pragma once

namespace Commons
{
	namespace Render
	{
		class IBindable
		{
		public:
			virtual void bind() = 0;
			virtual void unbind() = 0;

			virtual ~IBindable() {}
		};
	}
}

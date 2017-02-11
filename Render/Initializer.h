#pragma once
#include <Common/NonObject.h>

namespace Commons
{
	namespace Render
	{
		class Initializer : NonObject
		{
		public:
			static void Init();
			static void Destroy();
		};

		class ScopedInitializer
		{
		public:
			ScopedInitializer();
			~ScopedInitializer();
		};

	}
}
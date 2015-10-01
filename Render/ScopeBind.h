#pragma once
#include <Common/NonCopyable.h>
#include <Render/IBindable.h>

namespace Commons
{
	namespace Render
	{
		class ScopeBind : public NonCopyable
		{
		public:
			explicit ScopeBind(IBindable& bindable)
				: m_bindable(bindable)
			{
				m_bindable.bind();
			}

			~ScopeBind()
			{
				m_bindable.unbind();
			}
		private:
			IBindable& m_bindable;
		};
	}
}

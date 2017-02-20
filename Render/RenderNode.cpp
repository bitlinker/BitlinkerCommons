#include "RenderNode.h"

namespace Commons
{
	namespace Render
	{
		RenderNode::RenderNode()
			: mTranslation()
			, mChildren()
			, mParent()
			, mName()
			, mIsVisible(true)
			, mBBox()
            , mRenderable()
		{
		}

		RenderNode::RenderNode(const std::string& name)
			: mTranslation()
			, mChildren()
			, mParent()
			, mName(name)
			, mIsVisible(true)
			, mBBox()
            , mRenderable()
		{
		}

		// TODO: pass frustum for vis check here...
		void RenderNode::render(const glm::mat4& matrix)
		{
			if (mIsVisible)
			{
				// TODO: identity matrix optimization
				glm::mat4 nodeMatrix = matrix * mTranslation;

				// TODO: BBOX visibility check

				if (mRenderable)
                { 
                    mRenderable->render(nodeMatrix);
                }

				for (auto child : mChildren)
				{
					child->render(nodeMatrix);
				}
			}
		}

		void RenderNode::attachChild(RenderNodePtr& child)
		{
			assert(child);
			mChildren.push_back(child);
			child->setParent(shared_from_this());
		}

		bool RenderNode::removeChild(RenderNodePtr& child)
		{
			auto it = mChildren.begin();
			auto itEnd = mChildren.end();
			while (it != itEnd)
			{
				if (*it == child)
				{
					child->setParent(RenderNodeWeakPtr(shared_from_this()));
					mChildren.erase(it);
					return true;
				}
			}

			return false;
		}

		void RenderNode::removeAllChildren()
		{
			for (auto child : mChildren)
			{
				child->setParent(RenderNodeWeakPtr());
			}
			mChildren.clear();
		}

		const RenderNodeWeakPtr RenderNode::getParent() const
		{
			return mParent;
		}

		void RenderNode::setParent(const RenderNodeWeakPtr& parent)
		{
			mParent = parent;
		}
	}
}

#pragma once
#include <Render/RenderCommon.h>
#include <Render/AABB.h>
#include <memory>
#include <list>

namespace Commons
{
	namespace Render
	{
		class RenderNode;
		typedef std::shared_ptr<RenderNode> RenderNodePtr;
		typedef std::weak_ptr<RenderNode> RenderNodeWeakPtr;

        // TODO: move
        class IRenderable
        {
        public:
            virtual void render(const glm::mat4& matrix) = 0;
            virtual ~IRenderable() {};
        };
        typedef std::shared_ptr<IRenderable> IRenderablePtr;

        // TODO: not node; component system
		class RenderNode : public std::enable_shared_from_this<RenderNode>
		{
		public:
			RenderNode();
			explicit RenderNode(const std::string& name);
			virtual ~RenderNode() {};

			void render(const glm::mat4& matrix = glm::mat4(1.F));

			void attachChild(RenderNodePtr& child);
			bool removeChild(RenderNodePtr& child);
			void removeAllChildren();

			const glm::mat4& getTranslation() const { return mTranslation; }
			void setTranslation(const glm::mat4& translation) { mTranslation = translation; }

			const std::string& getName() const { return mName; }
			void setName(const std::string& name) { mName = name; }

			bool isVisible() const { return mIsVisible; }
			void setVisible(bool visible) { mIsVisible = visible; }

			const AABB& getBBox() const { return mBBox; }
			void setBBox(const AABB& bbox) { mBBox = bbox; }

            const IRenderablePtr& getRenderable() const { return mRenderable; }
            void setRenderable(const IRenderablePtr& renderable) { mRenderable = renderable; }

		private:
			const RenderNodeWeakPtr getParent() const;
			void setParent(const RenderNodeWeakPtr& parent);

		private:
			glm::mat4 mTranslation;
			std::list<RenderNodePtr> mChildren;
			RenderNodeWeakPtr mParent;
			std::string mName;
			bool mIsVisible;
			AABB mBBox;
            IRenderablePtr mRenderable;
		};
	}
}

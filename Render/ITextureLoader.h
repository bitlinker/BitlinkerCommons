#pragma once
#include <Render/RenderCommon.h>
#include <Render/Texture.h>

namespace Commons
{
	namespace Render
	{
        class ITextureLoader
        {
        public:
            virtual bool loadTexture(const std::string& name, const void* extra, const TexturePtr& texture) = 0;
            virtual ~ITextureLoader() {};
        };
        typedef std::shared_ptr<ITextureLoader> ITextureLoaderPtr;
	}
}

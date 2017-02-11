#include <Render/SharedTextureMgr.h>
#include <Common/StringUtils.h>
#include <Logger/Log.h>
#include <functional>

using namespace std::placeholders;

namespace Commons
{
    namespace Render
    {
        SharedTextureMgr::SharedTextureMgr(Context* context)
            : mContext(context) // TODO: init members            
        {
            LOG_DEBUG("SharedTextureMgr created");
        }

        SharedTextureMgr::~SharedTextureMgr()
        {
            LOG_DEBUG("SharedTextureMgr destroyed");
        }

        void SharedTextureMgr::addLoader(const ITextureLoaderPtr& loader, uint32_t priority)
        {
            mTextureLoaders.insert(std::make_pair(priority, loader));
        }

        bool SharedTextureMgr::removeLoader(const ITextureLoaderPtr& loader)
        {
            auto it = mTextureLoaders.begin();
            const auto itEnd = mTextureLoaders.end();
            while (it != itEnd)
            {
                if (it->second == loader)
                {
                    mTextureLoaders.erase(it);
                    return true;
                }
                ++it;
            }
            return false;
        }
        
        void SharedTextureMgr::removeLoaders()
        {
            mTextureLoaders.clear();
        }

        SharedTexturePtr SharedTextureMgr::getTexture(const std::string& name, const void* extra)
        {
            TTextureKey key(name); // TODO: key, names

            auto it = mTextures.find(key);
            if (it != mTextures.end()) // Returning texture from cache
            {
                return it->second.lock();
            }
            else // Try to load it
            {
                TexturePtr tex = loadTexture(name, extra);
                if (!tex)
                {
                    LOG_WARN("Texture not found: %s", key.c_str());
                    return nullptr;
                }

                SharedTexturePtr result(new SharedTexture(tex), std::bind(&SharedTextureMgr::deleteTexture, this, _1));
                mTextures.insert(std::make_pair(key, result));
                mTexturesToDelete.insert(std::make_pair(result.get(), key));
                return result;
            }
        }

        // TODO: loadparams, texture key?
        TexturePtr SharedTextureMgr::loadTexture(const std::string& name, const void* extra)
        {
            LOG_DEBUG("Loading texture: %s", name.c_str());
            TexturePtr tex(new Texture(mContext)); // TODO: create texture in context

            auto it = mTextureLoaders.begin();
            const auto itEnd = mTextureLoaders.end();
            while (it != itEnd)
            {
                if (it->second->loadTexture(name, extra, tex))
                {
                    return tex;
                }
                ++it;
            }
            return nullptr;
        }

        void SharedTextureMgr::deleteTexture(SharedTexture* texPtr)
        {            
            auto itKey = mTexturesToDelete.find(texPtr);
            assert(itKey != mTexturesToDelete.end());

            const TTextureKey& key = itKey->second;
            LOG_DEBUG("Deleting texture: %s", key.c_str());
            
            auto itTex = mTextures.find(key);
            assert(itTex != mTextures.end());
            
            mTextures.erase(itTex);
            mTexturesToDelete.erase(itKey);
        }
    }
}

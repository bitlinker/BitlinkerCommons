#pragma once
#include <Render/RenderCommon.h>
#include <Render/Texture.h>
#include <Render/ITextureLoader.h>
#include <Common/NonCopyable.h>
#include <memory>
#include <map>

namespace Commons
{
    namespace Render
    {
        class SharedTexture
        {
            friend class SharedTextureMgr;
        private:
            SharedTexture(const TexturePtr& tex)
                : mTex(tex)
            {
            }

        public:
            ~SharedTexture() {}

            const TexturePtr& get() const { return mTex; }

        private:
            TexturePtr mTex;
        };
        typedef std::shared_ptr<SharedTexture> SharedTexturePtr;
        typedef std::weak_ptr<SharedTexture> SharedTextureWeakPtr;

        /**
        * Shared texture manager
        * Stores textures until they have at least one reference
        * Should be destroyed after every texture is released
        */
        class SharedTextureMgr : public NonCopyable
        {
        public:
            SharedTextureMgr(Context* context);
            virtual ~SharedTextureMgr();

            void addLoader(const ITextureLoaderPtr& loader, uint32_t priority = 0);
            bool removeLoader(const ITextureLoaderPtr& loader);
            void removeLoaders();

            SharedTexturePtr getTexture(const std::string& name, const void* extra = nullptr);

        private:
            TexturePtr loadTexture(const std::string& name, const void* extra);
            void deleteTexture(SharedTexture* texPtr);

        private:
            typedef std::string TTextureKey;
            std::map<TTextureKey, SharedTextureWeakPtr> mTextures;      // key: texture key, value: texture weak pointer
            std::map<SharedTexture*, TTextureKey> mTexturesToDelete;          // key: raw texture pointer, value: texture key
            std::multimap<uint32_t, ITextureLoaderPtr> mTextureLoaders; // key: priority, value: loader object
            Context* mContext;
        };

        typedef std::shared_ptr<SharedTextureMgr> SharedTextureMgrPtr;
    }
}

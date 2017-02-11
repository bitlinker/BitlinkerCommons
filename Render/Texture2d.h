#pragma once
#include <Render/RenderCommon.h>
#include <Render/Texture.h>
#include <memory>

namespace Commons
{
	namespace Render
	{
		class Texture2d : public Texture
		{
		public:
            // TODO: construct from image data
			Texture2d(Context* context);
			virtual ~Texture2d();

            void setData(uint32_t level, FormatMode format, uint32_t width, uint32_t height, const uint8_t* pixels);
            void setSubData(uint32_t level, FormatMode format, uint32_t x, uint32_t y, uint32_t width, uint32_t height, const uint8_t* pixels);
		};

		typedef std::shared_ptr<Texture2d> Texture2dPtr;
		typedef std::weak_ptr<Texture2d> Texture2dWeakPtr;
	}
}

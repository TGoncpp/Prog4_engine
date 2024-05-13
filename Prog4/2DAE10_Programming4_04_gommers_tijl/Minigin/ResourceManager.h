#pragma once
#include <string>
#include <memory>
#include <utility>
#include "Singleton.h"

namespace TG
{
	class Texture2D;
	class Font;
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		void Init(const std::string& data);
		std::unique_ptr<Texture2D> LoadTexture(const std::string& file, float scale = 1, std::pair<int, int>spriteRowColum = std::make_pair (1,1)) const;
		std::shared_ptr<Texture2D> LoadTexture(const std::string& file, bool, float scale = 1, std::pair<int, int>spriteRowColum = std::make_pair(1, 1)) const;
		std::shared_ptr<Font> LoadFont(const std::string& file, unsigned int size) const;
	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;
		std::string m_dataPath;
	};
}

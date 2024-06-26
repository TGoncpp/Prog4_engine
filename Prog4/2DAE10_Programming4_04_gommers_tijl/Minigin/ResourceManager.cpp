#include <stdexcept>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "ResourceManager.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"

void TG::ResourceManager::Init(const std::string& dataPath)
{
	m_dataPath = dataPath;

	if (TTF_Init() != 0)
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

std::unique_ptr<TG::Texture2D> TG::ResourceManager::LoadTexture(const std::string& file, float scale, std::pair<int, int>spriteRowColum) const
{
	const auto fullPath = m_dataPath + file;
	auto texture        = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}
	return std::make_unique<Texture2D>(texture, scale, spriteRowColum);
}

std::shared_ptr<TG::Texture2D> TG::ResourceManager::LoadTexture(const std::string& file, bool , float scale, std::pair<int, int>spriteRowColum ) const
{
	const auto fullPath = m_dataPath + file;
	auto texture        = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}
	return std::make_shared<Texture2D>(texture, scale, spriteRowColum);
}

std::shared_ptr<TG::Font> TG::ResourceManager::LoadFont(const std::string& file, unsigned int size) const
{
	return std::make_shared<Font>(m_dataPath + file, size);
}

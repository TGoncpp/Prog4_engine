#pragma once
#include <glm/vec2.hpp>
#include <utility>

struct SDL_Texture;
namespace TG
{
	/**
	 * Simple RAII wrapper for an SDL_Texture
	 */
	class Texture2D final 
	{
	public:
		SDL_Texture* GetSDLTexture() const;
		explicit Texture2D(SDL_Texture* texture, float scale = 1.f, std::pair<int,int> spriteRowColum = std::make_pair(1,1));
		~Texture2D();

		glm::ivec2 GetSize() const;
		float GetScale()const;

		Texture2D(const Texture2D &)               = delete;
		Texture2D(Texture2D &&)                    = delete;
		Texture2D & operator= (const Texture2D &)  = delete;
		Texture2D & operator= (const Texture2D &&) = delete;

		std::pair<int, int> GetSpriteRowColum()const { return m_SpriteRowColum; }

	private:
		SDL_Texture* m_texture;
		std::pair<int, int> m_SpriteRowColum;
		float m_Scale{ 1.f };
	};
}

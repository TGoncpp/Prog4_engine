#pragma once
#include "GameObject.h"

namespace Game
{

	class Winner final : public TG::GameObject
	{
	public:
		Winner(std::shared_ptr<TG::Texture2D> textureEndSPTR, std::shared_ptr<TG::Texture2D> textureNewscorSPTR, 
			std::shared_ptr<TG::Font> fontSPTR, std::shared_ptr<TG::Font> fontBigSPTR);
		~Winner() = default;
		Winner(Winner&&) = delete;
		Winner(const Winner&) = delete;
		Winner& operator=(Winner&&) = delete;
		Winner& operator=(const Winner&) = delete;

		virtual void HandleInput(const glm::vec2&)override;
	};

}
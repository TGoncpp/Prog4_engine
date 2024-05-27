#pragma once
#include "GameObject.h"

class TG::Texture2D;
namespace Game
{
	class MenuScreen : public TG::GameObject
	{
	public:
		MenuScreen(const std::shared_ptr < TG::Texture2D>& selectionTexture, const std::shared_ptr<TG::Texture2D>& arrowTexture, const std::shared_ptr < TG::Font>& font);
		virtual ~MenuScreen()                           = default;
		MenuScreen(const MenuScreen& other)             = delete;
		MenuScreen(MenuScreen&& other)                  = delete;
		MenuScreen& operator=(const MenuScreen& other)  = delete;
		MenuScreen& operator=(MenuScreen&& other)       = delete;

		virtual void HandleInput(const glm::vec2&);

	private:
		glm::vec3 m_ArrowPosition{};
		const std::pair<int, int> m_MinMaxSelectionValue{ std::make_pair(0,2) };
		TG::RenderComponent* m_ArrowTextureCompPtr{ nullptr };
		float m_TextHeight{};
		int m_Selected{ 0 };

		int MoveArrow(int movement);
	};
}
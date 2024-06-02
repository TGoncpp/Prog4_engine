#include "MenuScreen.h"
#include "Texture2D.h"
#include "TextComponent.h"
#include "RenderComponent.h"

Game::MenuScreen::MenuScreen(const std::shared_ptr < TG::Texture2D>& selectionTexture, const std::shared_ptr<TG::Texture2D>& arrowTexture, const std::shared_ptr < TG::Font>& font)
{
	const float borderX              { 80.f };
	const float textStartHeigt       { 250.f };
	const float titleStartHeigt      { 15.f };
	const float spaceBetweenArrowText{ 10.f };

	//Title
	auto comp = AddComponent<TG::RenderComponent>(this, selectionTexture);
	TG::RenderComponent* TextureComp = static_cast<TG::RenderComponent*>(comp);
	TextureComp->SetOffset(glm::vec3{ borderX, titleStartHeigt, 0.f });

	//Arrow
	comp                = AddComponent<TG::RenderComponent>(this, arrowTexture);
	m_ArrowTextureCompPtr = static_cast<TG::RenderComponent*>(comp);
	m_ArrowPosition = glm::vec3{ borderX, textStartHeigt, 0.f };
	m_ArrowTextureCompPtr->SetOffset(m_ArrowPosition);
	const float arrowWidth{ m_ArrowTextureCompPtr->GetTexture()->GetSize().x + spaceBetweenArrowText} ;

	//Text off options
	TG::TextComponent* TextComp = AddComponent<TG::TextComponent>(this, "Single Player ", font, glm::vec3{ borderX + arrowWidth, textStartHeigt, 0.f });
	m_TextHeight = TextComp->GetTextSize().y;
	AddComponent<TG::TextComponent>(this, "VS  "   , font, glm::vec3{ borderX + arrowWidth, textStartHeigt + m_TextHeight    , 0.f });
	AddComponent<TG::TextComponent>(this, "Co-Op  ", font, glm::vec3{ borderX + arrowWidth, textStartHeigt + m_TextHeight * 2, 0.f });

}

void Game::MenuScreen::HandleInput(const glm::vec2& upDown)
{
	int movement{ static_cast<int>(upDown.y) };
	MoveArrow(movement);
}

int Game::MenuScreen::MoveArrow(int movement)
{
	m_Selected += movement;
	if (m_Selected >= m_MinMaxSelectionValue.second)
		m_Selected = m_MinMaxSelectionValue.second;

	else if (m_Selected <= m_MinMaxSelectionValue.first)
		m_Selected = m_MinMaxSelectionValue.first;

	m_ArrowTextureCompPtr->SetOffset(glm::vec3(m_ArrowPosition.x, m_ArrowPosition.y + m_Selected * m_TextHeight, 0.f));

	return m_Selected;
}

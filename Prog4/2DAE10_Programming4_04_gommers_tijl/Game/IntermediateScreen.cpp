#include "IntermediateScreen.h"
#include "TextComponent.h"
#include "RenderComponent.h"

Game::IntermedateScreen::IntermedateScreen(std::vector<std::shared_ptr<TG::Texture2D>> vTextures, std::shared_ptr<TG::Font> font)
	:m_vTextureSPtr{vTextures}
{
	const glm::vec2 ImagePos{ 65.f, 50.f };
	const float messageX{ 65.f };
	const float messageY{ 250.f };
	const float spaceMessageY{ 350.f };

	AddComponent<TG::RenderComponent>(this, vTextures[0]);
	AddComponent<TG::TextComponent>(this, "SINGLE PLAYER ", font, glm::vec3{ messageX, messageY, 0.f });
	AddComponent<TG::TextComponent>(this, "Press SPACE ", font, glm::vec3{ messageX, spaceMessageY, 0.f });
	SetLocalPosition(ImagePos);
}

void Game::IntermedateScreen::ApplyGameMode(int gameModeValue)
{
	//set new images
	auto comp = GetComponent<TG::RenderComponent>();
	comp->SetTexture(m_vTextureSPtr[gameModeValue]);

	//set new message
	auto textComp = GetComponent<TG::TextComponent>();
	textComp->SetText(m_vMessages[gameModeValue]);
	textComp->Update(0.f);

}

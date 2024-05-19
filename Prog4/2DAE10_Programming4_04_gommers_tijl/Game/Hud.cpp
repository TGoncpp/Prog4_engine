#include "Hud.h"
#include "RenderComponent.h"
#include "scoreDisplay.h"
#include "healthDisplay.h"

Game::Hud::Hud(std::vector<Character*> vCharacters, std::vector<std::shared_ptr<TG::Texture2D>> vTextures, std::shared_ptr<TG::Font> font)
{
	//Create all renderComponents
	int index{};
	for (auto& comp : m_mTextureRenderRefrences)
	{
		auto baseComp = AddComponent<TG::RenderComponent>(this, vTextures[index++]);
		comp.second = static_cast<TG::RenderComponent*>(baseComp);
	}
	
	//Score
	SetTextComponent(glm::vec2{ 15.f, 150.f }, "score", font);
	AddComponent<ScoreComponent>(this, vCharacters, m_mTextRenderRefrences["score"]);

	//Player
	SetTextComponent(glm::vec2{ 15.f, 100.f }, "Player 1", font);

	//Lvl
	std::string text = "level  " + std::to_string(m_Level);
	SetTextComponent(glm::vec2{ 510.f, 100.f }, "level", font, text);

	//round
	text = "Round  " + std::to_string(m_Round);
	SetTextComponent(glm::vec2{ 510.f, 150.f }, "round", font, text);


	//set cube target
	m_mTextureRenderRefrences["targetCube"]->SetOffset(glm::vec3{ 15.f, 50.f, 0.f });
	auto rowColum = m_mTextureRenderRefrences["targetCube"]->GetTexture()->GetSpriteRowColum();
	auto Comp = AddComponent<TG::SpriteComponent>(this, rowColum.second, rowColum.first, false);
	auto sprite = static_cast<TG::SpriteComponent*>(Comp);
	sprite->SetTexture(m_mTextureRenderRefrences["targetCube"]);
	sprite->UpdateFrame((m_Round - 1) + (m_Level - 1) * rowColum.second);


}

void Game::Hud::SetTextComponent(const glm::vec2& offset, const std::string& key, std::shared_ptr<TG::Font> font, std::string text)
{
	if (text == "")
		text = key;
	auto Comp = AddComponent<TG::TextComponent>(this, text, font);
	m_mTextRenderRefrences[key] = static_cast<TG::TextComponent*>(Comp);
	m_mTextRenderRefrences[key]->SetOffset(offset);
}
	

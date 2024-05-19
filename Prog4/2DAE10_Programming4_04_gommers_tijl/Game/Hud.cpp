#include "Hud.h"
#include "RenderComponent.h"
#include "scoreDisplay.h"
#include "HealthComponent.h"

Game::Hud::Hud(std::vector<Character*> vCharacters, std::vector<std::shared_ptr<TG::Texture2D>> vTextures, std::shared_ptr<TG::Font> font)
{
	const float borderOffset{ 15.f };

	//Create all renderComponents
	int index{};
	for (auto& comp : m_mTextureRenderRefrences)
	{
		if (comp.first == "health" || comp.first == "health2")
		{
			auto baseComp = AddComponent<TG::RenderComponent>(this, vTextures[index]);
			comp.second = static_cast<TG::RenderComponent*>(baseComp);
			continue;
		}
		auto baseComp = AddComponent<TG::RenderComponent>(this, vTextures[index++]);
		comp.second = static_cast<TG::RenderComponent*>(baseComp);
	}
	
	//Score
	SetTextComponent(glm::vec2{ borderOffset, 150.f }, "score", font);
	AddComponent<ScoreComponent>(this, vCharacters, m_mTextRenderRefrences["score"]);

	//Player
	SetTextComponent(glm::vec2{ borderOffset, 100.f }, "Player 1", font);

	//Lvl
	std::string text = "level  " + std::to_string(m_Level);
	SetTextComponent(glm::vec2{ 510.f, 100.f }, "level", font, text);

	//round
	text = "Round  " + std::to_string(m_Round);
	SetTextComponent(glm::vec2{ 510.f, 150.f }, "round", font, text);

	//set cube target
	m_mTextureRenderRefrences["targetCube"]->SetOffset(glm::vec3{ 15.f, 50.f, 0.f });
	auto rowColum = m_mTextureRenderRefrences["targetCube"]->GetTexture()->GetSpriteRowColum();
	auto Comp = AddComponent<TG::SpriteComponent>(this, rowColum.second, rowColum.first, false, m_mTextureRenderRefrences["targetCube"]);
	auto sprite = static_cast<TG::SpriteComponent*>(Comp);
	sprite->UpdateFrame((m_Round - 1) + (m_Level - 1) * rowColum.second);

	//Set Health
	const float startHeight = 175.f;
	const int offset = m_mTextureRenderRefrences["health"]->GetTexture()->GetSize().y;
	m_mTextureRenderRefrences["health"]->SetOffset(glm::vec3{ borderOffset, startHeight + offset, 0.f });
	m_mTextureRenderRefrences["health2"]->SetOffset(glm::vec3{ borderOffset, startHeight + offset * 2, 0.f });
	m_mTextureRenderRefrences["health3"]->SetOffset(glm::vec3{ borderOffset, startHeight + offset * 3, 0.f });
	std::vector vHearths{ m_mTextureRenderRefrences["health"] , m_mTextureRenderRefrences["health2"] , m_mTextureRenderRefrences["health3"] };
	AddComponent<HealthComponent>(this, vCharacters[0], vHearths);


}

void Game::Hud::SetTextComponent(const glm::vec2& offset, const std::string& key, std::shared_ptr<TG::Font> font, std::string text)
{
	if (text == "")
		text = key;
	auto Comp = AddComponent<TG::TextComponent>(this, text, font);
	m_mTextRenderRefrences[key] = static_cast<TG::TextComponent*>(Comp);
	m_mTextRenderRefrences[key]->SetOffset(offset);
}
	

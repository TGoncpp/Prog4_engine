#include "Hud.h"
#include "RenderComponent.h"
#include "scoreDisplay.h"
#include "HealthComponent.h"

Game::Hud::Hud(std::vector<Character*> vCharacters, std::vector<Character*> vCharactersPlayer2
	, std::vector<std::shared_ptr<TG::Texture2D>> vTextures, std::shared_ptr<TG::Font> font)
{
	const float borderOffset{ 15.f };
	const float Player2X{ 525.f };

	//Create all renderComponents
	int index{};
	for (auto& comp : m_mTextureRenderRefrences)
	{
		if (comp.first != "background" && comp.first != "healthPlayer2-3")
		{
			auto baseComp = AddComponent<TG::RenderComponent>(this, vTextures[index]);
			comp.second = static_cast<TG::RenderComponent*>(baseComp);
			continue;
		}
		auto baseComp = AddComponent<TG::RenderComponent>(this, vTextures[index++]);
		comp.second = static_cast<TG::RenderComponent*>(baseComp);
	}
	
	//Score Player1
	SetTextComponent(glm::vec2{ borderOffset, 150.f }, "Score", font);
	auto comp = AddComponent<ScoreComponent>(this, vCharacters, m_mTextRenderRefrences["Score"]);
	m_ScorePlayer1Ptr = static_cast<ScoreComponent*>(comp);

	//Player
	SetTextComponent(glm::vec2{ borderOffset, 100.f }, "Player 1", font);

	//Score Player2
	SetTextComponent(glm::vec2{ Player2X, 150.f }, "Score", font);
	comp = AddComponent<ScoreComponent>(this, vCharactersPlayer2, m_mTextRenderRefrences["Score"]);
	m_ScorePlayer2Ptr = static_cast<ScoreComponent*>(comp);
	
	//Player
	SetTextComponent(glm::vec2{ Player2X, 100.f }, "Player 2", font);

	//Lvl
	std::string text = "Level  " + std::to_string(m_Level);
	SetTextComponent(glm::vec2{ 250.f, 440.f }, "level", font, text);

	//round
	text = "Round  " + std::to_string(m_Round);
	SetTextComponent(glm::vec2{ 350.f, 440.f  }, "round", font, text);

	//set cube target
	AddComponent<TG::TextComponent>(this, "Target", font, glm::vec3{ 15.f, 25.f, 0.f });
	m_mTextureRenderRefrences["targetCube"]->SetOffset(glm::vec3{ 15.f, 50.f, 0.f });
	auto rowColum = m_mTextureRenderRefrences["targetCube"]->GetTexture()->GetSpriteRowColum();
	auto Comp = AddComponent<TG::SpriteComponent>(this, rowColum.second, rowColum.first, false, m_mTextureRenderRefrences["targetCube"]);
	auto sprite = static_cast<TG::SpriteComponent*>(Comp);
	sprite->UpdateFrame((m_Round - 1) + (m_Level - 1) * rowColum.second);

	//Set Health player 1
	const float startHeight = 175.f;
	const int offset = m_mTextureRenderRefrences["health"]->GetTexture()->GetSize().y;
	m_mTextureRenderRefrences["health"]->SetOffset(glm::vec3{ borderOffset, startHeight + offset, 0.f });
	m_mTextureRenderRefrences["health2"]->SetOffset(glm::vec3{ borderOffset, startHeight + offset * 2, 0.f });
	m_mTextureRenderRefrences["health3"]->SetOffset(glm::vec3{ borderOffset, startHeight + offset * 3, 0.f });
	std::vector vHearths{ m_mTextureRenderRefrences["health"] , m_mTextureRenderRefrences["health2"] , m_mTextureRenderRefrences["health3"] };
	comp = AddComponent<HealthComponent>(this, vCharacters[0], vHearths);
	m_HealthPlayer1Ptr = static_cast<HealthComponent*>(comp);

	
	//Set Health player 2
	m_mTextureRenderRefrences["healthPlayer2-1"]->SetOffset(glm::vec3{ Player2X, startHeight + offset, 0.f });
	m_mTextureRenderRefrences["healthPlayer2-2"]->SetOffset(glm::vec3{ Player2X, startHeight + offset * 2, 0.f });
	m_mTextureRenderRefrences["healthPlayer2-3"]->SetOffset(glm::vec3{ Player2X, startHeight + offset * 3, 0.f });
	m_mTextureRenderRefrences["healthPlayer2-1"]->SetVisibility(false);
	m_mTextureRenderRefrences["healthPlayer2-2"]->SetVisibility(false);
	m_mTextureRenderRefrences["healthPlayer2-3"]->SetVisibility(false);
	std::vector vHearthsPlayer2{ m_mTextureRenderRefrences["healthPlayer2-1"] , m_mTextureRenderRefrences["healthPlayer2-2"] , m_mTextureRenderRefrences["healthPlayer2-3"] };
	comp = AddComponent<HealthComponent>(this, vCharactersPlayer2[0], vHearthsPlayer2);
	m_HealthPlayer2Ptr = static_cast<HealthComponent*>(comp);

	m_mTextRenderRefrences["Score"]->SetVisibility(false);
	m_mTextRenderRefrences["Player 2"]->SetVisibility(false);


}

void Game::Hud::ApplyGameMode(int gameMode)
{
	if (gameMode == 2)
	{
		//Set visibility
		m_mTextureRenderRefrences["healthPlayer2-1"]->SetVisibility(true);
		m_mTextureRenderRefrences["healthPlayer2-2"]->SetVisibility(true);
		m_mTextureRenderRefrences["healthPlayer2-3"]->SetVisibility(true);

		m_mTextRenderRefrences["Score"]->SetVisibility(true);
		m_mTextRenderRefrences["Player 2"]->SetVisibility(true);

		m_HealthPlayer2Ptr->ResetHealth();
		m_ScorePlayer2Ptr->ResetScore();

	}
	else
	{
		m_mTextureRenderRefrences["healthPlayer2-1"]->SetVisibility(false);
		m_mTextureRenderRefrences["healthPlayer2-2"]->SetVisibility(false);
		m_mTextureRenderRefrences["healthPlayer2-3"]->SetVisibility(false);

		m_mTextRenderRefrences["Score"]->SetVisibility(false);
		m_mTextRenderRefrences["Player 2"]->SetVisibility(false);

	}
		//Reset values
		m_HealthPlayer1Ptr->ResetHealth();
		m_ScorePlayer1Ptr->ResetScore();
}

void Game::Hud::SetTextComponent(const glm::vec2& offset, const std::string& key, std::shared_ptr<TG::Font> font, std::string text)
{
	if (text == "")
		text = key;
	auto Comp = AddComponent<TG::TextComponent>(this, text, font);
	m_mTextRenderRefrences[key] = static_cast<TG::TextComponent*>(Comp);
	m_mTextRenderRefrences[key]->SetOffset(offset);
}
	

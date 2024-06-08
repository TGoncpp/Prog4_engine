#include "Winner.h"
#include "highscoreComponent.h"
#include "textcomponent.h"
#include "rendercomponent.h"

Game::Winner::Winner(std::shared_ptr<TG::Texture2D> textureEndSPTR, std::shared_ptr<TG::Texture2D> textureNewscorSPTR,
	std::shared_ptr<TG::Font> fontSPTR, std::shared_ptr<TG::Font> fontBigSPTR)
{
	const float startX{ 100.f };
	const float startTextY{ 300.f };
	const float startTextX{ 150.f };
	const float startIDX{ 210.f };
	const float startIDY{ 300.f };
	const float distanceBetweenLetters{ 25.f };

	auto comp = AddComponent<TG::RenderComponent>(this, textureEndSPTR);
	comp->SetOffset(glm::vec3{ startX, 10.f, 0.f });
	AddComponent<TG::RenderComponent>(this, textureNewscorSPTR);

	auto textComp = AddComponent<TG::TextComponent>(this, "score: N/A", fontSPTR, glm::vec3{ startTextX , startTextY, 0.f });
	const float offsetY = textComp->GetTextSize().y;
	const int numOffScores{ 5 };
	for (int i{ 1 }; i < numOffScores; ++i)
	{
		AddComponent<TG::TextComponent>(this, "score: N/A", fontSPTR, glm::vec3{ startTextX , startTextY + i * offsetY, 0.f });
	}

	textComp = AddComponent<TG::TextComponent>(this, "A", fontBigSPTR, glm::vec3{ startIDX , startIDY, 0.f });
	const float offsetX = textComp->GetTextSize().x + distanceBetweenLetters;
	const int numOffIDLetters{ 4 };
	for (int i{ 1 }; i < numOffIDLetters; ++i)
	{
		AddComponent<TG::TextComponent>(this, "A", fontBigSPTR, glm::vec3{ startIDX + i * offsetX, startIDY, 0.f });
	}
	AddComponent<Game::HighscoreComponent>(this, numOffScores, numOffIDLetters);

	//OnActivateInput.OnNotifyAll(true);
}

void Game::Winner::HandleInput(const glm::vec2& signal)
{
	if (CheckComponent<HighscoreComponent>())
	{
		auto comp = GetComponent<HighscoreComponent>();
		comp->SetLetter(signal);
	}
}

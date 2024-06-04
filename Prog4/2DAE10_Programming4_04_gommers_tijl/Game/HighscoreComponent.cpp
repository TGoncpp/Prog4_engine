#include "HighscoreComponent.h"
#include "gameObject.h"
#include "textComponent.h"

Game::HighscoreComponent::HighscoreComponent(TG::GameObject* owner)
	:BaseComponent(owner)
{
	m_vTextWritersPtr = owner->GetAllComponent<TG::TextComponent>();
}

void Game::HighscoreComponent::GetDataFromFile()
{
}

void Game::HighscoreComponent::CompareHighscore(int )
{
}

void Game::HighscoreComponent::AdjustStorredScore()
{
}

void Game::HighscoreComponent::DisplayScore()
{
}

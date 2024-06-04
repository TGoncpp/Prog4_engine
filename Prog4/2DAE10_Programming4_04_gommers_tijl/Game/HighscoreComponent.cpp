#include "HighscoreComponent.h"
#include "gameObject.h"
#include "textComponent.h"
#include <fstream>
#include <sstream>
#include "sceneManager.h"


Game::HighscoreComponent::HighscoreComponent(TG::GameObject* owner)
	:BaseComponent(owner)
{
	m_vTextWritersPtr = owner->GetAllComponent<TG::TextComponent>();
	m_NumOffScores = static_cast<int>(m_vTextWritersPtr.size());
	GetDataFromFile();
	
	CreateFile();
}

void Game::HighscoreComponent::Update(float)
{
	if (m_ScoreIsSet)
		return;
	m_ScoreIsSet = true;
	std::string key{ "TT" };
	int score{ static_cast<TG::WinnerState*>(TG::SceneManager::GetInstance().GetMenuOffState(TG::EMenuState::winner))->GetScore() };
	CompareHighscore(score, key);
	DisplayScore();
	CreateFile();
}

void Game::HighscoreComponent::ResetScoreFlag()
{
	m_ScoreIsSet = false;
}

void Game::HighscoreComponent::GetDataFromFile()
{
	std::ifstream input;
	input.open(m_TextFile);
	if (input.is_open())
	{
		std::string line;
		while (std::getline(input, line))
		{
			int score{};
			std::string name;

			std::stringstream stream(line);
			std::string chunk;
			while (stream >> chunk)
			{
				if (score == 0)
					score = std::stoi(chunk);
				else
					name = chunk;
			}
			m_mHighscore.insert( std::make_pair(score, name));
		}
	}
	input.close();
}

void Game::HighscoreComponent::CompareHighscore(int score, const std::string& name)
{
	//If open spots left
	if (m_mHighscore.size() < m_NumOffScores)
	{
		m_mHighscore.insert(std::make_pair(score, name));
		return;
	}

	//look for the lowest to compare
	auto it = --m_mHighscore.cend();
	int lowestScore{ it->first};
	
	//stop if lowest score is higher then the new one
	if (lowestScore > score)
		return;

	m_mHighscore.erase(it);

	m_mHighscore.insert(std::make_pair(score, name));
}

void Game::HighscoreComponent::DisplayScore()const
{
	std::string text;
	int i{ 1 };
	for (auto& score : m_mHighscore)
	{
		text = std::to_string(i)+ ". " + score.second + "   " + std::to_string(score.first);
		m_vTextWritersPtr[i++ - 1]->SetText(text);
	}
}

void Game::HighscoreComponent::CreateFile()const
{
	std::ofstream output;
	output.open(m_TextFile);
	for (const auto& line : m_mHighscore)
	{
		output << line.first << " ";
		output << line.second << "\n";
	}

	output.close();
}


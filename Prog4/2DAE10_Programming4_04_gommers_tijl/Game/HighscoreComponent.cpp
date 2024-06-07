#include "HighscoreComponent.h"
#include "gameObject.h"
#include "textComponent.h"
#include "RenderComponent.h"
#include <fstream>
#include <sstream>
#include "sceneManager.h"
#include <iostream>


Game::HighscoreComponent::HighscoreComponent(TG::GameObject* owner, int numOfScores, int numOfLettersID)
	:BaseComponent(owner),
	m_NumOffScores{numOfScores},
	m_NumOffLettersID{numOfLettersID}
{
	auto comps = owner->GetAllComponent<TG::TextComponent>();
	for (int i{}; i < comps.size(); ++i)
	{
		if (i < m_NumOffScores)
			m_vTextWritersPtr.emplace_back(comps[i]);
		else if (i < m_NumOffScores + m_NumOffLettersID)
			m_vTextIDWriterPtr.emplace_back(comps[i]);
	}

	m_NewHighTexturePtr = owner->GetAllComponent<TG::RenderComponent>()[1];
	SetScoreVisible(false);

	GetDataFromFile();
	//CreateFile();

}

Game::HighscoreComponent::~HighscoreComponent()
{
	CreateFile();
}

void Game::HighscoreComponent::Update(float)
{
	if (m_IsNewScoreEvaluated)
		return;
	
	if (!m_ScoreIsSet)
	{
		int score{ static_cast<TG::WinnerState*>(TG::SceneManager::GetInstance().GetMenuOffState(TG::EMenuState::winner))->GetScore() };
		m_GotNewHighscore = CompareHighscore(score);
		m_ScoreIsSet = true;
		m_ActiveLetter = 0;
	}

	if (m_GotNewHighscore)
	{
		m_IsNewScoreEvaluated = EnterNameIsFinished();
	}

	
	if (m_IsNewScoreEvaluated)
	{
		DisplayScore();
	}
	
	
}

void Game::HighscoreComponent::ResetScoreFlag()
{
	m_ScoreIsSet = false;
}

void Game::HighscoreComponent::SetLetter(const glm::vec2& signal)
{
	if (signal.x == 0.f)
	{
		std::string letter = m_vTextIDWriterPtr[m_ActiveLetter]->GetText();
		for (char& c : letter)
		{
			if (c == 'Z') c = 'A'; // Wrap around for 'z'
			else c++; // Increment other characters
		}
		//letter = std::to_string(std::stoi(c[0]) + static_cast<int>(signal.y));
		m_vTextIDWriterPtr[m_ActiveLetter]->SetText(letter);
	}
	else if (signal.y == 0.f && signal.x == 1.f)
	{
		m_ActiveLetter++;
	}
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

bool Game::HighscoreComponent::CompareHighscore(int score)
{
	//If open spots left
	if (m_mHighscore.size() < m_NumOffScores)
	{
		m_NewHighscor = score;
		return true;
	}

	//look for the lowest to compare
	auto it = --m_mHighscore.cend();
	int lowestScore{ it->first};
	
	//stop if lowest score is higher then the new one
	if (lowestScore > score)
		return false;

	//Have a new score so new name need to be set
	m_NewHighscor = score;
	return true;
	
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

void Game::HighscoreComponent::SetScoreVisible(bool visseble)
{
	for (auto& letter : m_vTextWritersPtr)
	{
		letter->SetVisibility(visseble);
	}
}

void Game::HighscoreComponent::SetNewScoreVisible(bool visseble)
{
	m_NewHighTexturePtr->SetVisibility(visseble);
	for (auto& letter : m_vTextIDWriterPtr)
	{
		letter->SetVisibility(visseble);
	}
}

bool Game::HighscoreComponent::EnterNameIsFinished()
{
	std::string name;
	//check if every letter is set
	return  (m_ActiveLetter >= m_NumOffLettersID);

	//m_mHighscore.insert(std::make_pair(m_NewHighscor, name));
	return true;
}


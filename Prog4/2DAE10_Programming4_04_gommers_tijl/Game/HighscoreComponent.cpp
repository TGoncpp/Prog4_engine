#include "HighscoreComponent.h"
#include "gameObject.h"
#include "textComponent.h"
#include "RenderComponent.h"
#include <fstream>
#include <sstream>
#include "sceneManager.h"
#include "MenuState.h"
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

}

Game::HighscoreComponent::~HighscoreComponent()
{
	CreateFile();
}

void Game::HighscoreComponent::Update(float)
{
	if (!m_ScoreIsSet)
	{
		int score{ static_cast<TG::WinnerState*>(TG::SceneManager::GetInstance().GetMenuOffState(TG::EMenuState::winner))->GetScore() };
		m_OwnerPTR->OnActivateInput.OnNotifyAll(true);
		m_ActiveLetter = 0;

		m_IsFinalScreenShowing = !CompareHighscore(score);
		if (m_IsFinalScreenShowing)
		{
			DisplayScore();
			SetScoreVisible(true);
			SetNewScoreVisible(false);
		}
		else
		{
			SetScoreVisible(false);
			SetNewScoreVisible(true);
		}
		m_ScoreIsSet = true;
	}

}

void Game::HighscoreComponent::ResetScoreFlag()
{
	m_ScoreIsSet = false;
}

void Game::HighscoreComponent::SetLetter(const glm::vec2& signal)
{
	if (m_IsFinalScreenShowing && signal.y == 0.f && signal.x == 1.f)
	{
		//if final screen is showing, return to new menuscreen when pressed ENTER
		TG::SceneManager::GetInstance().GetMenustate()->OnStateSwitch.OnNotifyAll(TG::EMenuState::intro, -1);
		m_OwnerPTR->OnActivateInput.OnNotifyAll(false);
		return;
	}

	if (signal.x == 0.f)
	{
		std::string letter = m_vTextIDWriterPtr[m_ActiveLetter]->GetText();
		for (char& c : letter)
		{
			if (c == 'Z') 
				c = 'A'; 
			else
				c =  c + static_cast<char>(signal.y); 
		}
		m_vTextIDWriterPtr[m_ActiveLetter]->SetText(letter);
	}
	else if (signal.y == 0.f && signal.x == 1.f)
	{
		m_NewHighscoreName += m_vTextIDWriterPtr[m_ActiveLetter]->GetText();
		m_ActiveLetter++;
		if (m_ActiveLetter >= m_NumOffLettersID)
		{
			m_ActiveLetter = 0;
			m_mHighscore.insert(std::make_pair(m_NewHighscor, m_NewHighscoreName));
			SetScoreVisible(true);
			SetNewScoreVisible(false);
			DisplayScore();
			m_IsFinalScreenShowing = true;
		}
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
	m_mHighscore.erase(it);
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


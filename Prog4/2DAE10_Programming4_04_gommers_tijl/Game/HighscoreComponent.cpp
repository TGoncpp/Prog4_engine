#include "HighscoreComponent.h"
#include "gameObject.h"
#include "textComponent.h"
#include <fstream>
#include <sstream>


Game::HighscoreComponent::HighscoreComponent(TG::GameObject* owner)
	:BaseComponent(owner)
{
	m_vTextWritersPtr = owner->GetAllComponent<TG::TextComponent>();
	m_NumOffScores = static_cast<int>(m_vTextWritersPtr.size());
	GetDataFromFile();
	std::string key;
	CompareHighscore(500, key);
	CreateFile();
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
			m_mHighscore.insert( std::make_pair(name, score));
		}
	}
	input.close();
}

void Game::HighscoreComponent::CompareHighscore(int score, std::string& keyOfLowest)
{
	//If open spots left
	if (m_mHighscore.size() < m_NumOffScores)
	{
		m_mHighscore.insert(std::make_pair("new", score));
		return;
	}

	//look for the lowest to compare
	int lowestScore{ 10000000 };
	std::string lowestKey;
	for (const auto& line : m_mHighscore)
	{
		if (line.second < lowestScore)
		{
			lowestScore = line.second;
			lowestKey = line.first;
		}
	}
	auto it = std::find_if(m_mHighscore.cbegin(), m_mHighscore.cend(), [lowestScore](std::pair<std::string, int> el)
		{
			return el.second == lowestScore;
		});

	m_mHighscore.erase(it);

	if (lowestScore < score)
	{
		keyOfLowest = lowestKey;
	}
}

void Game::HighscoreComponent::DisplayScore()
{
}

void Game::HighscoreComponent::CreateFile()
{
	std::ofstream output;
	output.open(m_TextFile);
	for (const auto& line : m_mHighscore)
	{
		output << line.second << " ";
		output << line.first << "\n";
	}

	output.close();
}

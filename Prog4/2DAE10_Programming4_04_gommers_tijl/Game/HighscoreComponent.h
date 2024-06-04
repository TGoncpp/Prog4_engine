//---------------------------------------------
//Thanks to Mike Shah, one off my favourite youtuners

#pragma once
#include "BaseComponent.h"
#include <map>
#include <vector>
#include <string>

namespace Game
{
	class HighscoreComponent final : public TG::BaseComponent
	{
	public:
		HighscoreComponent(TG::GameObject* owner);
		virtual ~HighscoreComponent()override                    = default;
		HighscoreComponent& operator=(const HighscoreComponent&) = delete;
		HighscoreComponent& operator=(HighscoreComponent&&)      = delete;
		HighscoreComponent(const HighscoreComponent&)            = delete;
		HighscoreComponent(HighscoreComponent&&)                 = delete;

		virtual void Update(float);
		virtual void FixedUpdate(float) {};
		virtual void Render()const {};

		void ResetScoreFlag();

	private:
		std::multimap<int, std::string, std::greater<int>> m_mHighscore;
		std::vector<TG::TextComponent*> m_vTextWritersPtr;
		std::string m_TextFile{"highScore.txt"};
		int m_NumOffScores{};
		
		void GetDataFromFile();
		void CompareHighscore(int newScore, const std::string& name);
		void DisplayScore()const;
		void CreateFile()const;
		bool m_ScoreIsSet{ false };
		
	};
}


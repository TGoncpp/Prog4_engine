//---------------------------------------------
//Thanks to Mike Shah, one off my favourite youtuners
//Letter increment copied from copilot

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
		HighscoreComponent(TG::GameObject* owner, int numOfScores, int numOfLettersID);
		virtual ~HighscoreComponent()override;
		HighscoreComponent& operator=(const HighscoreComponent&) = delete;
		HighscoreComponent& operator=(HighscoreComponent&&)      = delete;
		HighscoreComponent(const HighscoreComponent&)            = delete;
		HighscoreComponent(HighscoreComponent&&)                 = delete;

		virtual void Update(float);
		virtual void FixedUpdate(float) {};
		virtual void Render()const {};

		void ResetScoreFlag();
		void SetLetter(const glm::vec2& signal);

	private:
		std::multimap<int, std::string, std::greater<int>> m_mHighscore;
		std::vector<TG::TextComponent*> m_vTextWritersPtr;
		std::vector<TG::TextComponent*> m_vTextIDWriterPtr;
		TG::RenderComponent*  m_NewHighTexturePtr{nullptr};
		std::string m_TextFile{"highScore.txt"};
		std::string m_NewHighscoreName;
		int m_NumOffScores{};
		int m_NumOffLettersID{};
		int m_NewHighscor{};
		int m_ActiveLetter{};
		bool m_IsFinalScreenShowing{ false };
		
		void GetDataFromFile();
		bool CompareHighscore(int newScore);
		void DisplayScore()const;
		void CreateFile()const;
		bool m_ScoreIsSet{ false };
		void SetScoreVisible(bool visseble);
		void SetNewScoreVisible(bool visseble);
		
	};
}


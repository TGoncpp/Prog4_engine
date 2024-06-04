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

		virtual void Update(float) {};
		virtual void FixedUpdate(float) {};
		virtual void Render()const {};

	private:
		std::map<std::string, int> m_mHighscore;
		std::vector<TG::TextComponent*> m_vTextWritersPtr;
		int m_NumOffScores{};
		
		void GetDataFromFile();
		void CompareHighscore(int newScore);
		void AdjustStorredScore();
		void DisplayScore();
		
	};
}


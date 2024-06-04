#pragma once
#include "BaseComponent.h"

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
		
	};
}


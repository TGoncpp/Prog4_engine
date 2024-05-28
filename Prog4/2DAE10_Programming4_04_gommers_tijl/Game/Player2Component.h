#pragma once
#include "BaseComponent.h"

namespace Game
{
	class Player2Component final : public TG::BaseComponent
	{
	public:
		Player2Component(TG::GameObject* owner)
			:BaseComponent{owner}{}
		
		virtual ~Player2Component()override                  = default;
		Player2Component& operator=(const Player2Component&) = delete;
		Player2Component& operator=(Player2Component&&)      = delete;
		Player2Component(const Player2Component&)            = delete;
		Player2Component(Player2Component&&)                 = delete;

		virtual void Update(float ) {};
		virtual void FixedUpdate(float ) {};
		virtual void Render()const {};
	};
}
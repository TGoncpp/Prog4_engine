#pragma once

#include "BaseComponent.h"
#include "Subject.h"

namespace Game
{
	enum class LootType
	{
		gold,
		silver,
		dirt
	};

	class LootComponent final : public TG::BaseComponent
	{
	public:
		LootComponent(TG::GameObject* owner)
			:TG::BaseComponent(owner)
		{
		}
		virtual ~LootComponent()
		{

		}
		LootComponent& operator=(const LootComponent&) = delete;
		LootComponent& operator=(LootComponent&&)      = delete;
		LootComponent(const LootComponent&)            = delete;
		LootComponent(LootComponent&&)                 = delete;


		TG::Subject<LootType> OnScoreChange;

		virtual void Update(float ) {  };
		virtual void FixedUpdate(float ) {  };
		virtual void Render()const {};

		void PickupLoot(const LootType& loot);

	};
}
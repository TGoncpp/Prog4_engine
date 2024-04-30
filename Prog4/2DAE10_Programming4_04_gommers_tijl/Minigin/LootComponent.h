#pragma once

#include "BaseComponent.h"
#include "Subject.h"

namespace TG
{
	enum class LootType
	{
		gold,
		silver,
		dirt
	};

	class LootComponent final : public BaseComponent
	{
	public:
		LootComponent(TG::GameObject* owner)
			:BaseComponent(owner)
		{
		}
		virtual ~LootComponent()
		{

		}
		LootComponent& operator=(const LootComponent&) = delete;
		LootComponent& operator=(LootComponent&&)      = delete;
		LootComponent(const LootComponent&)            = delete;
		LootComponent(LootComponent&&)                 = delete;


		Subject<LootType> OnScoreChange;

		virtual void Update(float ) {  };
		virtual void FixedUpdate(float ) {  };
		virtual void Render()const {};

		void PickupLoot(const LootType& loot);

	};
}
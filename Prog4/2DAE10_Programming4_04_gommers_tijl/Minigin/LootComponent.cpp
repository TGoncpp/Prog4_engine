#include "LootComponent.h"

void TG::LootComponent::PickupLoot(const LootType& loot)
{
	
	OnScoreChange.OnNotifyAll(loot);
}

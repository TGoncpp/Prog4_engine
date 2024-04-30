#include "LootComponent.h"
#include "serviceLocator.h"

void TG::LootComponent::PickupLoot(const LootType& loot)
{
	OnScoreChange.OnNotifyAll(loot);
	Locator::getAudio().playSound("Jump");
}

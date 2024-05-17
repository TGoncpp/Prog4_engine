#include "LootComponent.h"
#include "serviceLocator.h"

void Game::LootComponent::PickupLoot(const LootType& loot)
{
	OnScoreChange.OnNotifyAll(loot);
	TG::Locator::getAudio().playSound("Jump");
}

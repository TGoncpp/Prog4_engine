#include "HealthComponent.h"
#include "GameObject.h"
#include "serviceLocator.h"

Game::HealthComponent::HealthComponent(TG::GameObject* owner, int startHealth)
	:TG::BaseComponent(owner),
	 m_Health{startHealth}
{
}

void Game::HealthComponent::DecreaseHealth(int decrement)
{
	m_Health -= decrement;
	OnHealthChange.OnNotifyAll();
	TG::Locator::getAudio().playSound("Hit");

	if (m_Health <= 0)
	{
		OnDead.OnNotifyAll(m_OwnerPTR->GetName());
		TG::Locator::getAudio().playSound("Swearing");
	}
}

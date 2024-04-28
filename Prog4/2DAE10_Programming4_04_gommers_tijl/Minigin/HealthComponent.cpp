#include "HealthComponent.h"
#include "GameObject.h"
#include "serviceLocator.h"

TG::HealthComponent::HealthComponent(TG::GameObject* owner, int startHealth)
	:BaseComponent(owner),
	 m_Health{startHealth}
{
}

void TG::HealthComponent::DecreaseHealth(int decrement)
{
	m_Health -= decrement;
	OnHealthChange.OnNotifyAll();
	Locator::getAudio().playSound("Hit");

	if (m_Health <= 0)
	{
		OnDead.OnNotifyAll(m_OwnerPTR->GetName());
		Locator::getAudio().playSound("Swearing");
	}
}

#include "HealthComponent.h"
#include "GameObject.h"

TG::HealthComponent::HealthComponent(TG::GameObject* owner, int startHealth)
	:BaseComponent(owner),
	 m_Health{startHealth}
{
}

void TG::HealthComponent::DecreaseHealth(int decrement)
{
	m_Health -= decrement;
	OnHealthChange.OnNotifyAll();
	if (m_Health <= 0)
	{
		OnDead.OnNotifyAll(m_OwnerPTR->GetName());
	}
}

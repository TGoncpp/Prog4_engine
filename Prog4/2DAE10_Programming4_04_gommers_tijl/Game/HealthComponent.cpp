#include "HealthComponent.h"
#include "GameObject.h"
#include "serviceLocator.h"

Game::HealthComponent::HealthComponent(TG::GameObject* owner, Character* Qbert, std::vector<TG::RenderComponent*> vHearths)
	:TG::BaseComponent(owner),
	m_vHearthRenderCompRef{vHearths},
	m_Subject{Qbert}
{
	Qbert->OnDead.AddObserver(this);
}

Game::HealthComponent::~HealthComponent()
{
	m_Subject->OnDead.RemoveObserver(this);
}

void Game::HealthComponent::Notify()
{
	DecreaseHealth(1);
}

void Game::HealthComponent::DecreaseHealth(int decrement)
{
	m_Health -= decrement;

	if (m_Health <= 0)
	{
		OnGameOver.OnNotifyAll();
		return;
	}
	m_vHearthRenderCompRef[m_Health - 1]->SetVisibility(false);
}

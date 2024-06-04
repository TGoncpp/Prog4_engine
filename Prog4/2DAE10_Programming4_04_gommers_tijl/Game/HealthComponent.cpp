#include "HealthComponent.h"
#include "GameObject.h"
#include "serviceLocator.h"
#include "SceneManager.h"


Game::HealthComponent::HealthComponent(TG::GameObject* owner, Character* Qbert, std::vector<TG::RenderComponent*> vHearths)
	:TG::BaseComponent(owner),
	m_vHearthRenderCompRef{vHearths},
	m_Subject{Qbert}
{
	Qbert->OnShowCurse.AddObserver(this);
}

Game::HealthComponent::~HealthComponent()
{
	m_Subject->OnShowCurse.RemoveObserver(this);
}

void Game::HealthComponent::ResetHealth()
{
	m_Health = 4;
	for (auto& hearth : m_vHearthRenderCompRef)
		hearth->SetVisibility(true);
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
		TG::SceneManager::GetInstance().GetMenustate()->GameOver();
		return;
	}
	m_vHearthRenderCompRef[m_Health - 1]->SetVisibility(false);
}

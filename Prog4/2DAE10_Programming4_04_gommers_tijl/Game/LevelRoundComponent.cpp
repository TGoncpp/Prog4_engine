#include "LevelRoundComponent.h"

Game::LvlRoundComponent::LvlRoundComponent(TG::GameObject* owner)
	:BaseComponent(owner)
{
}

void Game::LvlRoundComponent::Update(float time)
{
	if (m_CurrentTransferTime <= 0.f)
		return;

	m_CurrentTransferTime -= time;
	if (m_CurrentTransferTime <= 0.f)
	{
		m_CurrentTransferTime = 0.f;
		OnFinishTransfer.OnNotifyAll();
	}
}

void Game::LvlRoundComponent::NextRound()
{
	m_CurrentTransferTime = m_TransferTime;
	++m_CurrentRound;

	if (m_CurrentRound >= m_MaxRound)
	{
		++m_CurrentLvl;
		m_CurrentRound = 0;
	}

	OnNextPhase.OnNotifyAll(m_CurrentRound, m_CurrentLvl);
}


#include "LevelRoundComponent.h"

Game::LvlRoundComponent::LvlRoundComponent(TG::GameObject* owner)
	:BaseComponent(owner)
{
}

void Game::LvlRoundComponent::Update(float time)
{
	if (!m_IsTransferring)
		return;

	m_CurrentTransferTime -= time;
	OnAnim.OnNotifyAll(time);
	if (m_CurrentTransferTime <= 0.f)
	{
		m_CurrentTransferTime = 0.f;
		m_IsTransferring = false;
		NextRound();
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

void Game::LvlRoundComponent::StartAnim()
{
	if (m_IsTransferring)return;

	m_CurrentTransferTime = m_TransferTime;
	m_IsTransferring = true;
}

void Game::LvlRoundComponent::Reset()
{
	m_CurrentLvl = 1;
	m_CurrentRound = 1;
}


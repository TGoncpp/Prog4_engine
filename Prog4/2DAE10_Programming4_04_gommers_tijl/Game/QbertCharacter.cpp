#include "QbertCharacter.h"
#include "RenderComponent.h"
#include "Player2Component.h"
#include "Grid.h"
#include "MenuState.h"
#include "MovementComponent.h"


Game::QbertCharacter::QbertCharacter(const glm::vec2& position, std::shared_ptr<TG::Texture2D> texuteSPTR, const glm::vec2& jumpOffset, std::shared_ptr<TG::Texture2D> curseTex)
	:Character(position, texuteSPTR, jumpOffset)
{
	m_Name = "Qbert";

	//curse texture
	auto comp = AddComponent<TG::RenderComponent>(this, curseTex);
	m_RenderCurseCompRefrence = static_cast<TG::RenderComponent*>(comp);
	m_RenderCurseCompRefrence->SetOffset(glm::vec3{ 0.f, -30.f, 0.f });
	m_RenderCurseCompRefrence->SetVisibility(false);

	//States
	m_PossibleStates.insert(std::make_pair(EState::lift, std::make_unique<Lift>(this)));
	m_PossibleStates[EState::lift]->OnStateSwitch.AddObserver(this);
	m_PossibleStates[EState::dead]->OnShowCurse.AddObserver(this);
	m_CharacterState = m_PossibleStates[EState::idle].get();
}

void Game::QbertCharacter::Notify(bool isVisible)
{
	SetCurseVisibility(isVisible);
}

//void Game::QbertCharacter::Notify()
//{
//	auto state = m_CharacterState->GetState();
//	if (state == EState::dissable)
//		return;
//
//	m_CharacterState = (state == EState::freeze)? m_PossibleStates[EState::dead].get() : m_PossibleStates[EState::freeze].get();
//}

void Game::QbertCharacter::ActivateInput(bool isActive)
{
	OnActivateInput.OnNotifyAll(isActive);
}

void Game::QbertCharacter::ApplyGameMode(int gameMode, int)
{
	TG::EGameMode mode = static_cast<TG::EGameMode>(gameMode);

	//activate player 2 if coop
	if (CheckComponent<Player2Component>())
	{
		if (mode == TG::EGameMode::coop)
		{
			SetPositionOnGridByIndex(6, 0, m_JumpOffset);
			m_CharacterState = m_PossibleStates[EState::idle].get();
		}

		else
		{
			SetPositionOnGridByIndex(12, 0, m_JumpOffset);
			m_CharacterState = m_PossibleStates[EState::dissable].get();
		}
	}
	//player 1
	else
	{
		if (mode == TG::EGameMode::coop)
			SetPositionOnGridByIndex(0, 6, m_JumpOffset);

		else
			SetPositionOnGridByIndex(0, 0, m_JumpOffset);

		m_CharacterState = m_PossibleStates[EState::idle].get();
	}
	//Make sure MoveComponent is not halfway movement
	if (CheckComponent<MovementComponent>())
		GetComponent<MovementComponent>()->ResetForNewMode();
}

void Game::QbertCharacter::SetCurseVisibility(bool isVisible)
{
	m_RenderCurseCompRefrence->SetVisibility(isVisible);
}

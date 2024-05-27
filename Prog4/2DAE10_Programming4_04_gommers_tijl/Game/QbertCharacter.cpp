#include "QbertCharacter.h"
#include "RenderComponent.h"


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
	m_PossibleStates[EState::dead]->OnDead.AddObserver(this);
	m_PossibleStates.insert(std::make_pair(EState::dissable, std::make_unique<Dissable>(this)));
	m_CharacterState = m_PossibleStates[EState::dissable].get();
}

void Game::QbertCharacter::Notify(bool isVisible)
{
	SetCurseVisibility(isVisible);
}

void Game::QbertCharacter::ActivateInput(bool isActive)
{
	 m_CharacterState = isActive ? m_PossibleStates[EState::idle].get() : m_PossibleStates[EState::dissable].get();
}

void Game::QbertCharacter::SetCurseVisibility(bool isVisible)
{
	m_RenderCurseCompRefrence->SetVisibility(isVisible);
}

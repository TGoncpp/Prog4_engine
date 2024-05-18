#include "QbertCharacter.h"
#include "RenderComponent.h"


Game::QbertCharacter::QbertCharacter(const glm::vec2& position, std::shared_ptr<TG::Texture2D> texuteSPTR, const glm::vec2& jumpOffset, std::shared_ptr<TG::Texture2D> curseTex)
	:Character(position, texuteSPTR, jumpOffset)
{
	//curse texture
	auto comp = AddComponent<TG::RenderComponent>(this, curseTex);
	m_RenderCompRefrence = static_cast<TG::RenderComponent*>(comp);
	m_RenderCompRefrence->SetOffset(glm::vec3{ 0.f, -30.f, 0.f });
	m_RenderCompRefrence->SetVisibility(false);

	//States
	m_PossibleStates.insert(std::make_pair(EState::lift, std::make_unique<Lift>(this)));
	m_PossibleStates[EState::lift]->OnStateSwitch.AddObserver(this);
	m_PossibleStates[EState::dead]->OnDead.AddObserver(this);

}

void Game::QbertCharacter::Notify(bool isVisible)
{
	SetCurseVisibility(isVisible);
}

void Game::QbertCharacter::SetCurseVisibility(bool isVisible)
{
	m_RenderCompRefrence->SetVisibility(isVisible);
}

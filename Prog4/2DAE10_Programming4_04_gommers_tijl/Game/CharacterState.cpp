#include "CharacterState.h"
#include "SpriteComponent.h"
#include "GameObject.h"


Game::CharacterStateComponent::CharacterStateComponent(TG::GameObject* ownerObjRefrence)
	:BaseComponent(ownerObjRefrence)
{
	
}

void Game::CharacterStateComponent::UpdateProgressState(const glm::vec2& direction)
{
	if (direction.x == 1)
	{
		m_State = CharacterState::rightDown;
	}
	else if (direction.x == -1)
	{
		m_State = CharacterState::leftUp;
	}
	else if (direction.y == 1)
	{
		m_State = CharacterState::rightUp;
	}
	else if (direction.y == -1)
	{
		m_State = CharacterState::leftDown;
	}

	if (m_OwnerPTR->CheckComponent<TG::SpriteComponent>())
		m_OwnerPTR->GetComponent<TG::SpriteComponent>()->UpdateFrame(static_cast<int>(m_State));
}


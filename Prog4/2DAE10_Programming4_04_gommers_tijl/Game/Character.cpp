#include "Character.h"
#include "MovementComponent.h"
#include "SpriteComponent.h"
#include "RenderComponent.h"

Game::Character::Character(const glm::vec2& position, std::shared_ptr<TG::Texture2D> textureSPTR)
{
	SetLocalPosition(position);
	//AddComponent<TG::MovementComponent>(this);
	//AddComponent<TG::RenderComponent>(this, textureSPTR);
	//AddComponent<TG::SpriteComponent>(this, 4, 1, false);
}



void Game::Character::UpdateState(const glm::vec2& direction)
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
		m_State = CharacterState::leftdown;
	}
}

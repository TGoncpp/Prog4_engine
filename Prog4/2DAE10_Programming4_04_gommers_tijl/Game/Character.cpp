#include "Character.h"
#include "MovementComponent.h"
#include "SpriteComponent.h"
#include "RenderComponent.h"
#include "CharacterState.h"
#include "Texture2D.h"

Game::Character::Character(const glm::vec2& position, std::shared_ptr<TG::Texture2D> textureSPTR, const glm::vec2& jumpOffset, int gridSize )
{
	const int spriteRows{ 1 }, spriteColum{ 4 };
	glm::vec2 cubePos{ position.x - (textureSPTR->GetSize().x / (spriteColum * 2.f)), position.y + (textureSPTR->GetSize().y/ spriteRows) };
	SetLocalPosition(cubePos);
	AddComponent<TG::MovementComponent>(this, glm::vec2{0.f, 0.f}, jumpOffset, gridSize);
	AddComponent<TG::RenderComponent>(this, textureSPTR);
	AddComponent<TG::SpriteComponent>(this, 4, 1, false);
	AddComponent<Game::CharacterStateComponent>(this);

}

void Game::Character::SetState(const glm::vec2& direction)
{
	if (CheckComponent<Game::CharacterStateComponent>())
		GetComponent<Game::CharacterStateComponent>()->UpdateState(direction);

	m_GridPostion.first += static_cast<int>(direction.x);
	m_GridPostion.second += static_cast<int>(direction.y);
}

void Game::Character::UpdateGrid()
{
	OnCubeInteraction.OnNotifyAll(m_GridPostion);
}


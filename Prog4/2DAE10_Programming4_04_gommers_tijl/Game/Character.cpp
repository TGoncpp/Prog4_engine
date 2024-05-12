#include "Character.h"
#include "MovementComponent.h"
#include "SpriteComponent.h"
#include "RenderComponent.h"
#include "CharacterState.h"
#include "Texture2D.h"

#include<iostream>

Game::Character::Character(const glm::vec2& position, std::shared_ptr<TG::Texture2D> textureSPTR, const glm::vec2& jumpOffset, int gridSize, std::pair<int, int> spriteSheet)
{
	const int spriteRows{ spriteSheet.first }, spriteColum{ spriteSheet.second };
	glm::vec2 cubePos{ position.x - (textureSPTR->GetSize().x / (spriteColum * 2.f)), position.y - (textureSPTR->GetSize().y/ spriteRows) + jumpOffset.y /**1.4f*/ };
	SetLocalPosition(cubePos);
	AddComponent<TG::MovementComponent>(this, glm::vec2{0.f, 0.f}, jumpOffset, gridSize);
	AddComponent<TG::RenderComponent>(this, textureSPTR);
	AddComponent<TG::SpriteComponent>(this, spriteSheet.second, spriteSheet.first, false);
	//AddComponent<Game::CharacterStateComponent>(this);

	m_PossibleStates.insert(std::make_pair("idle", std::make_unique<Idle>(this)));
	m_PossibleStates.insert(std::make_pair("walking", std::make_unique<WalkingQbertState>(this)));
	m_CharacterState = m_PossibleStates["idle"].get();

}

void Game::Character::HandleInput(const glm::vec2& direction)
{
	m_CharacterState->InputHandeling(direction);
}

void Game::Character::Update(float time)
{
	m_CharacterState->Update(time);
}

void Game::Character::NewState(const std::string& newState)
{
	m_CharacterState->OnExit();

	if (m_PossibleStates.contains(newState))
	{
		m_CharacterState = m_PossibleStates[newState].get();
		m_CharacterState->OnEnter(m_Direction);
	}
	else
	{
		std::cout << "does not contain new state\n";
	}
}

void Game::Character::UpdateGridPosition(const glm::vec2& direction)
{
	m_GridPostion.first -= static_cast<int>(direction.y);
	m_GridPostion.second += static_cast<int>(direction.x);
}

void Game::Character::UpdateGrid(bool isMoving)
{
	OnCubeInteraction.OnNotifyAll(m_GridPostion, m_Type, isMoving);
}

void Game::Character::SetPositionOnGridByIndex(int toLeft, int ToBelow, const glm::vec2& jumpOffset)
{
	m_GridPostion = std::make_pair(toLeft, ToBelow);
	glm::vec2 oldPos{ GetLocalPosition() };
	glm::vec2 jumpOffsetLeft{ -jumpOffset.x, jumpOffset.y };
	glm::vec2 newPos; 
	newPos = oldPos + static_cast<float>(ToBelow) * jumpOffset + static_cast<float>(toLeft) * jumpOffsetLeft;

	SetLocalPosition(newPos);
}

void Game::Character::SetCharacterType(const ECharacterType& newType)
{
	m_Type = newType;
}

void Game::Character::CollisionCheck(const ECharacterType& dominantType, std::pair<int, int> GridPostion)
{
	if (GridPostion != m_GridPostion)return;

	if (static_cast<int>(m_Type) - static_cast<int>(dominantType) == -1 && m_Type == ECharacterType::red)
	{
		--m_Health;
		std::cout << "red lose life\n";
	}
	else if (static_cast<int>(m_Type) - static_cast<int>(dominantType) == -1 && m_Type == ECharacterType::green)
	{
		++m_Score;
		std::cout << "score = "<< m_Score << "\n";
		std::cout << "green lose life\n";
	}

}

void Game::Character::SetDirection(const glm::vec2& newDirection)
{
	m_Direction = newDirection;
}

#include "Character.h"
#include "MovementComponent.h"
#include "SpriteComponent.h"
#include "RenderComponent.h"
#include "Texture2D.h"

#include<iostream>

Game::Character::Character(const glm::vec2& gridPosition, std::shared_ptr<TG::Texture2D> textureSPTR, const glm::vec2& jumpOffset)
{
	const std::pair<int, int> spriteRowsColums{ textureSPTR->GetSpriteRowColum()};
	glm::vec2 posOnCube{ gridPosition.x - (textureSPTR->GetSize().x / (spriteRowsColums.second * 2.f)), gridPosition.y - (textureSPTR->GetSize().y/ spriteRowsColums.first) + jumpOffset.y /**1.4f*/ };
	SetLocalPosition(posOnCube);

	//Add components
	AddComponent<Game::MovementComponent>(this, jumpOffset);
	AddComponent<TG::RenderComponent>(this, textureSPTR);
	AddComponent<TG::SpriteComponent>(this, spriteRowsColums.second, spriteRowsColums.first, false);

	//Add States
	m_PossibleStates.insert(std::make_pair(EState::idle, std::make_unique<Idle>(this)));
	m_PossibleStates[EState::idle]->OnStateSwitch.AddObserver(this);
	m_PossibleStates.insert(std::make_pair(EState::walking, std::make_unique<WalkingQbertState>(this)));
	m_PossibleStates[EState::walking]->OnStateSwitch.AddObserver(this);
	m_PossibleStates.insert(std::make_pair(EState::falling, std::make_unique<Falling>(this, 1.5f)));
	m_PossibleStates[EState::falling]->OnStateSwitch.AddObserver(this);
	m_PossibleStates.insert(std::make_pair(EState::dead, std::make_unique<Dead>(this, 1.f)));
	m_PossibleStates[EState::dead]->OnStateSwitch.AddObserver(this);
	m_PossibleStates.insert(std::make_pair(EState::respawn, std::make_unique<ReSpawn>(this, posOnCube, 50.f)));
	m_PossibleStates[EState::respawn]->OnStateSwitch.AddObserver(this);
	
	m_CharacterState = m_PossibleStates[EState::idle].get();
}

void Game::Character::Notify(const EState& state)
{
	if (m_PossibleStates.contains(state))
	{
		auto currentType = m_CharacterState->GetState();
		switch (currentType)
		{
		case EState::idle:
			if (state != EState::dead && state != EState::walking)
				return;
			break;
		case EState::walking:
			if (state != EState::dead && state != EState::idle && state != EState::lift && state != EState::falling)
				return;
			break;
		case EState::falling:
			if (state != EState::dead )
				return;
			break;
		case EState::dead:
			if (state != EState::respawn )
				return;
			break;
		case EState::respawn:
			if (state != EState::idle )
				return;
			break;
		case EState::lift:
			if (state != EState::respawn )
				return;
			break;
		}

		m_CharacterState = m_PossibleStates[state].get();
		m_CharacterState->OnEnter(m_Direction);
	}
	else
	{
		std::cout << "does not contain new state\n";
	}
}

void Game::Character::OnSubjectDestroy()
{
	//m_PossibleStates[EState::dead]->OnStateSwitch.RemoveObserver(this);
}

void Game::Character::HandleInput(const glm::vec2& direction)
{
	m_CharacterState->InputHandeling(direction);
}

void Game::Character::Update(float time)
{
	m_CharacterState->Update(time);
}
void Game::Character::FixedUpdate(float time)
{
	m_CharacterState->FixedUpdate(time);
}

void Game::Character::UpdateGridPosition(const glm::vec2& direction)
{
	m_GridPostion.first  -= static_cast<int>(direction.y);
	m_GridPostion.second += static_cast<int>(direction.x);
}

void Game::Character::UpdateGrid(bool isMoving)
{
	OnCubeInteraction.OnNotifyAll(this, isMoving);
}

void Game::Character::SetPositionOnGridByIndex(int toLeft, int ToBelow, const glm::vec2& jumpOffset)
{
	m_GridPostion = std::make_pair(toLeft, ToBelow);
	glm::vec2 oldPos{ GetLocalPosition() };
	glm::vec2 newPos{ TG::Transform::CalculateGridPosition(toLeft, ToBelow, jumpOffset, oldPos) };

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
		m_IsDead = true;// flag for state machine
	}
	else if (static_cast<int>(m_Type) - static_cast<int>(dominantType) == -1 && m_Type == ECharacterType::green)
	{
		OnScore.OnNotifyAll(m_Type);
		m_IsDead = true;// flag for state machine
	}

}

void Game::Character::SetDirection(const glm::vec2& newDirection)
{
	m_Direction = newDirection;
}

void Game::Character::JumpOfGrid(bool isFaling)
{
	if (m_CharacterState->GetState() == EState::lift)
		m_IsFalling = false;
	else
		m_IsFalling = isFaling;
}

void Game::Character::ResetLife()
{
	m_IsDead      = false;
	m_IsFalling   = false;
	m_GridPostion = std::make_pair(0, 0);
	UpdateGrid(false);
}


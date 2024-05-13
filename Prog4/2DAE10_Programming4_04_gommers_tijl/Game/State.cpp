#include "State.h"
#include "character.h"
#include "SpriteComponent.h"
#include "MovementComponent.h"
#include "Transform.h"
#include "serviceLocator.h"
#include <iostream>

//-------------------------------------------
//IDLE
//---------------------------------------------
void Game::Idle::InputHandeling(const glm::vec2& direction)
{
	m_OwnerObject->SetDirection( direction);
	m_OwnerObject->NewState(EState::walking); 

}

void Game::Idle::Update(float)
{
	if (m_OwnerObject->IsDead())
	{
		m_OwnerObject->NewState(EState::dead);
	}
}


//-------------------------------------------
//wALKING
//---------------------------------------------
void Game::WalkingQbertState::InputHandeling(const glm::vec2& )
{
	//No input allowed
}

void Game::WalkingQbertState::OnEnter(const glm::vec2& direction)
{
	int frame{ 0 };
	if (direction.x == 1)
	{
		frame = 2;
	}
	else if (direction.x == -1)
	{
		frame = 1;
	}
	else if (direction.y == 1)
	{
		frame = 0;
	}
	else if (direction.y == -1)
	{
		frame = 3;
	}

	if (m_OwnerObject->CheckComponent<TG::SpriteComponent>())
		m_OwnerObject->GetComponent<TG::SpriteComponent>()->UpdateFrame(frame);
	if (m_OwnerObject->CheckComponent<TG::MovementComponent>())
		m_OwnerObject->GetComponent<TG::MovementComponent>()->SetTargetLocation(direction);
	m_OwnerObject->UpdateGrid(true);
	m_OwnerObject->UpdateGridPosition(direction);

	TG::Locator::getAudio().playSound("Jump");
}

void Game::WalkingQbertState::Update(float time)
{
	if (!m_OwnerObject->CheckComponent<TG::MovementComponent>())
	{
		std::cout << "no vallid movementComponent\n";
		return;
	}
	auto comp = m_OwnerObject->GetComponent<TG::MovementComponent>();
	comp->FixedUpdate(time);
	if (comp->StoppedMoving() )
	{
		m_OwnerObject->UpdateGrid(false);
		if (m_OwnerObject->IsDead())
		{
			m_OwnerObject->NewState(EState::dead);
			return;
		}
		if (m_OwnerObject->IsFalling())
		{
			m_OwnerObject->NewState(EState::falling);
			return;
		}

		m_OwnerObject->NewState(EState::idle);
	}
	

}

void Game::WalkingQbertState::OnExit()
{
}


void Game::WalkingState::Update(float)
{

}

//-------------------------------------------
//FALLING
//---------------------------------------------
void Game::Falling::OnEnter(const glm::vec2&)
{
	m_CurrentFallTime = m_FallTime;
	m_FallPosition = m_OwnerObject->GetLocalPosition();
	m_CurrentFallPosition = m_FallPosition;

	TG::Locator::getAudio().playSound("Fall");

}

void Game::Falling::Update(float time)
{
	const float fallSpeed{200.f};
	m_CurrentFallPosition.y += time * fallSpeed;
	m_OwnerObject->SetLocalPosition(m_CurrentFallPosition);
	m_CurrentFallTime -= time;
	if (m_CurrentFallTime <= 0.f)
	{
		m_OwnerObject->NewState(EState::dead);
	}
}


//-------------------------------------------
//DEAD
//---------------------------------------------
void Game::Dead::OnEnter(const glm::vec2&)
{
	m_CurrentDieTime = m_TimeToDie;
	
	TG::Locator::getAudio().playSound("Swearing");
}

void Game::Dead::Update(float time)
{
	m_CurrentDieTime -= time;
	if (m_CurrentDieTime <= 0.f)
	{
		m_OwnerObject->NewState(EState::respawn);
	}
}


void Game::GreenDead::OnEnter(const glm::vec2&)
{
	m_CurrentDieTime = m_TimeToDie;

	TG::Locator::getAudio().playSound("Hit");
}

//-------------------------------------------
//RESPAWN
//---------------------------------------------
void Game::ReSpawn::OnEnter(const glm::vec2&)
{
	m_CurrentPos = m_StartPos - glm::vec2{ 0.f, m_SpawnHeight };
	m_OwnerObject->SetLocalPosition(m_CurrentPos);

	TG::Locator::getAudio().playSound("Fall");
}

void Game::ReSpawn::Update(float time)
{
	const float fallSpeed{ 80.f };
	m_CurrentPos.y += fallSpeed * time;
	m_OwnerObject->SetLocalPosition(m_CurrentPos);

	if (TG::Transform::IsEqualVector(m_StartPos, m_CurrentPos, 1.f))
	{
		m_OwnerObject->SetLocalPosition(m_StartPos);
		m_OwnerObject->NewState(EState::idle);
	}
}

void Game::ReSpawn::OnExit()
{
	m_OwnerObject->ResetLife();
}

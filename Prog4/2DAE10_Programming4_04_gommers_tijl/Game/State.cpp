#include "State.h"
#include "SpriteComponent.h"
#include "MovementComponent.h"
#include <iostream>

//-------------------------------------------
//IDLE
//---------------------------------------------
void Game::Idle::InputHandeling(const glm::vec2& direction)
{
	m_OwnerObject->SetDirection( direction);
	m_OwnerObject->NewState("walking");
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
	m_OwnerObject->UpdateGridPosition(direction);
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
	if (comp->StoppedMoving())
	{
		m_OwnerObject->NewState("idle");
	}

}

void Game::WalkingQbertState::OnExit()
{
}

void Game::WalkingState::Update(float)
{

}

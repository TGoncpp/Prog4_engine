#include "State.h"
#include "character.h"
#include "MovementComponent.h"
#include "Transform.h"
#include "serviceLocator.h"
#include <iostream>


Game::State::State(Character* owner)
	:IState{ owner } 
{
}


//-------------------------------------------
//IDLE
//---------------------------------------------
void Game::Idle::InputHandeling(const glm::vec2& direction)
{
	if (direction.x == 0 && direction.y == 0)
	{
		OnExit();
		OnStateSwitch.OnNotifyAll(EState::lift);
	}
	else if (direction.x == 1 && direction.y == 1)
	{
		OnExit();
		OnStateSwitch.OnNotifyAll(EState::respawn);
	}
	else
	{
		OnExit();
		m_OwnerObject->SetDirection( direction);
		OnStateSwitch.OnNotifyAll(EState::walking);
	}

	//m_OwnerObject->NewState(EState::walking); 

}

void Game::Idle::Update(float)
{
	if (m_OwnerObject->IsDead())
	{
		//m_OwnerObject->NewState(EState::dead);
		OnExit();
		OnStateSwitch.OnNotifyAll(EState::dead);
	}
}


//-------------------------------------------
//wALKING
//---------------------------------------------

Game::WalkingState::WalkingState(Character* owner)
	:State(owner)

{
	m_Type = EState::walking;
	if (m_OwnerObject->CheckComponent<MovementComponent>())
	{
		m_MoveComp = m_OwnerObject->GetComponent<MovementComponent>();
	}
	else
	{
		throw("no valid movementComponent");
	}

	if (m_OwnerObject->CheckComponent<TG::SpriteComponent>())
	{
		m_SpriteComp = m_OwnerObject->GetComponent<TG::SpriteComponent>();
	}
	else
	{
		throw("no valid spriteComponent");
	}
}

void Game::WalkingQbertState::InputHandeling(const glm::vec2& direction)
{
	if (direction.x == 0 && direction.y == 0)
	{
		OnExit();
		OnStateSwitch.OnNotifyAll(EState::lift);
		TG::Locator::getAudio().playSound("Disk Lift");

	}
	else if (direction.x == 1 && direction.y == 1)
	{
		OnExit();
		OnStateSwitch.OnNotifyAll(EState::respawn);
	}
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

	m_SpriteComp->UpdateFrame(frame);
	m_MoveComp->SetTargetLocationIndex(direction);
	m_OwnerObject->UpdateGrid(true);
	m_OwnerObject->UpdateGridPosition(direction);

	TG::Locator::getAudio().playSound("Jump");
}

void Game::WalkingQbertState::Update(float )
{
	
	
}

void Game::WalkingQbertState::FixedUpdate(float time)
{
	m_MoveComp->FixedUpdate(time);
	if (m_MoveComp->StoppedMoving())
	{
		m_OwnerObject->UpdateGrid(false);
		if (m_OwnerObject->IsDead())
		{
			//m_OwnerObject->NewState(EState::dead);
			OnExit();
			OnStateSwitch.OnNotifyAll(EState::dead);
			return;
		}
		if (m_OwnerObject->IsFalling())
		{
			//_OwnerObject->NewState(EState::falling);
			OnExit();
			OnStateSwitch.OnNotifyAll(EState::falling);
			return;
		}

		//m_OwnerObject->NewState(EState::idle);
		OnExit();
		OnStateSwitch.OnNotifyAll(EState::idle);
	}
}

void Game::WalkingQbertState::OnExit()
{
}



//-------------------------------------------
//FALLING
//---------------------------------------------
void Game::Falling::OnEnter(const glm::vec2&)
{
	m_CurrentFallTime     = m_FallTime;
	m_FallPosition        = m_OwnerObject->GetLocalPosition();
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
		//m_OwnerObject->NewState(EState::dead);
		OnStateSwitch.OnNotifyAll(EState::dead);
		OnExit();
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
		//m_OwnerObject->NewState(EState::respawn);
		OnStateSwitch.OnNotifyAll(EState::respawn);
		OnExit();
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
		//m_OwnerObject->NewState(EState::idle);
		OnStateSwitch.OnNotifyAll(EState::idle);
		OnExit();
	}
}

void Game::ReSpawn::OnExit()
{
	m_OwnerObject->ResetLife();
}

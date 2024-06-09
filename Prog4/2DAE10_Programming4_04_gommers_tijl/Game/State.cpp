#include "State.h"
#include "character.h"
#include "MovementComponent.h"
#include "Transform.h"
#include "serviceLocator.h"
#include <iostream>
#include "EggComponent.h"
#include "ChaseCharacter.h"
#include "sceneManager.h"


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

//------------------------------------------------------

void Game::GreenIdle::OnEnter(const glm::vec2&)
{
	int randNum = rand() % 10;
	bool left = randNum % 2 == 0;
	m_Direction =  left ? glm::vec2{1.f, 0.f} : glm::vec2{0.f, -1.f};
	
	m_CurrentIdletime = 0.f;
}

void Game::GreenIdle::Update(float time)
{
	if (m_OwnerObject->IsDead())
	{
		//m_OwnerObject->NewState(EState::dead);
		OnExit();
		OnStateSwitch.OnNotifyAll(EState::dead);
		return;
	}
	if (m_CurrentIdletime < m_Idletime)
	{
		m_CurrentIdletime += time;
		return;
	}
	m_CurrentIdletime = 0.f;

	m_OwnerObject->SetDirection(m_Direction);
	OnStateSwitch.OnNotifyAll(EState::walking);
}

//-----------------------------------------------------------

void Game::CoilyIdle::InputHandeling(const glm::vec2& direction)
{
	if (!m_IsEgg && TG::SceneManager::GetInstance().GetActiveGameModeIndex() == 1)
	{
		m_Direction = direction;
		m_OwnerObject->SetDirection(m_Direction);
		OnStateSwitch.OnNotifyAll(EState::walking);
	}
}

void Game::CoilyIdle::OnEnter(const glm::vec2&)
{
	int randNum = rand() % 10;
	bool left = randNum % 2 == 0;

	if (m_OwnerObject->CheckComponent<EggComponent>())
		m_IsEgg = m_OwnerObject->GetComponent<EggComponent>()->IsEgg();

	if (m_IsEgg)
		m_Direction = left ? glm::vec2{ 1.f, 0.f } : glm::vec2{ 0.f, -1.f };
	else
	{
		//if (TG::SceneManager::GetInstance().GetActiveGameModeIndex() == 1)
		//{
		//	m_CurrentIdletime = 0.f;
		//	return;
		//}

		if (m_OwnerObject->CheckComponent<ChaseCharacterComponent>())
			m_Direction = m_OwnerObject->GetComponent<ChaseCharacterComponent>()->GetDirectionToTarget();
	}


	m_CurrentIdletime = 0.f;
}

void Game::CoilyIdle::Update(float time)
{
	
	if (!m_IsEgg && TG::SceneManager::GetInstance().GetActiveGameModeIndex() == 1 )
	{
		m_CurrentIdletime = 0.f;
		return;
	}

	if (m_CurrentIdletime < m_Idletime)
	{
		m_CurrentIdletime += time;
		return;
	}
	m_CurrentIdletime = 0.f;

	m_OwnerObject->SetDirection(m_Direction);
	OnStateSwitch.OnNotifyAll(EState::walking);
}

//------------------------------------------------------------

void Game::WrongIdle::OnEnter(const glm::vec2&)
{
	//int randNum = rand() % 10;
	//bool left = randNum % 2 == 0;
	m_Direction = m_IsLeft ?glm::vec2{ 0.f, 1.f } : glm::vec2{ -1.f, 0.f } ;

	m_CurrentIdletime = 0.f;
}

//-------------------------------------------
//WALKING
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
	//when movement is in direction off the grid
	//check if on disc or nothing
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


//------------------------------------------------

void Game::WalkingGreenState::OnEnter(const glm::vec2& direction)
{
	//set sprite
	int frame{ 0 };
	if (direction.x == 1.f)
	{
		frame = m_IsSam ? 1 : 3;
	}
	
	else if (direction.y == -1.f)
	{
		frame = m_IsSam? 0 : 2;
	}
	
	//update grid and character
	m_SpriteComp->UpdateFrame(frame);
	m_MoveComp->SetTargetLocationIndex(direction);
	m_OwnerObject->UpdateGrid(true);
	m_OwnerObject->UpdateGridPosition(direction);
}

void Game::WalkingGreenState::FixedUpdate(float time)
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

//-------------------------------------------------------------------
void Game::WalkingCoilynState::OnEnter(const glm::vec2& direction)
{
	if (m_OwnerObject->CheckComponent<EggComponent>())
		m_IsEgg = m_OwnerObject->GetComponent<EggComponent>()->IsEgg();


	//set sprite
	int frame{ 0 };
	if (direction.x == 1)
	{
		frame = m_IsEgg? 1: 7;//7
	}
	else if (direction.x == -1)
	{
		frame = m_IsEgg ? 1 : 5;//5
	}
	else if (direction.y == -1)
	{
		frame = m_IsEgg ? 1 : 9;//9
	}
	else if (direction.y == 1)
	{
		frame = m_IsEgg ? 1 : 3;//3
	}

	//update grid and character
	m_SpriteComp->UpdateFrame(frame);
	m_MoveComp->SetTargetLocationIndex(direction);
	m_OwnerObject->UpdateGrid(true);
	m_OwnerObject->UpdateGridPosition(direction);
}

void Game::WalkingCoilynState::FixedUpdate(float time)
{
	m_MoveComp->FixedUpdate(time);

	if (m_MoveComp->StoppedMoving())
	{
		const float acceptedHeightDiff{ 5.f };
		if (m_IsEgg && abs(m_OwnerObject->GetLocalPosition().y - m_TransformHeight) < acceptedHeightDiff)
		{
			if (m_OwnerObject->CheckComponent<EggComponent>())
				m_OwnerObject->GetComponent<EggComponent>()->HatchEgg(true);

		}

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

void Game::WalkingCoilynState::OnExit()
{
	m_SpriteComp->DeUpdateFrame();
}

//-----------------------------------------------------------------------
void Game::WalkingWrongState::OnEnter(const glm::vec2& direction)
{

	//update grid and character
	m_SpriteComp->SetAutomaiticMode(true);
	m_MoveComp->SetTargetLocationIndex(direction);
	m_OwnerObject->UpdateGrid(true);
	m_OwnerObject->UpdateGridPosition(direction);
}

void Game::WalkingWrongState::Update(float time)
{
	m_SpriteComp->Update(time);
}

void Game::WalkingWrongState::FixedUpdate(float time)
{
	m_MoveComp->FixedUpdate(time);

	if (m_MoveComp->StoppedMoving())
	{
		m_OwnerObject->UpdateGrid(false);
		if (m_OwnerObject->IsDead())
		{
			OnExit();
			OnStateSwitch.OnNotifyAll(EState::dead);
			return;
		}
		if (m_OwnerObject->IsFalling())
		{
			OnExit();
			OnStateSwitch.OnNotifyAll(EState::falling);
			return;
		}

		OnExit();
		OnStateSwitch.OnNotifyAll(EState::idle);
	}
}

void Game::WalkingWrongState::OnExit()
{
	m_SpriteComp->SetAutomaiticMode(false);
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
	OnShowCurse.OnNotifyAll(true);
	m_OwnerObject->OnShowCurse.OnNotifyAll();
	TG::Locator::getAudio().playSound("Swearing");
}

void Game::Dead::Update(float time)
{
	m_CurrentDieTime -= time;
	if (m_CurrentDieTime <= 0.f)
	{
		OnStateSwitch.OnNotifyAll(EState::respawn);
		OnExit();
	}
}

void Game::Dead::OnExit()
{
	OnShowCurse.OnNotifyAll(false);
}


//-------------------------------------------------
void Game::GreenDead::OnEnter(const glm::vec2&)
{
	m_CurrentDieTime = m_TimeToDie;

	TG::Locator::getAudio().playSound("Hit");
}

//-------------------------------------------------
void Game::PurpleDead::OnEnter(const glm::vec2&)
{
	m_CurrentDieTime = m_TimeToDie;
	if (m_OwnerObject->CheckComponent<EggComponent>())
		m_OwnerObject->GetComponent<EggComponent>()->HatchEgg(false);
	
	if (m_OwnerObject->CheckComponent<TG::SpriteComponent>())
		m_OwnerObject->GetComponent<TG::SpriteComponent>()->UpdateFrame(1);
}

//-------------------------------------------
//RESPAWN
//---------------------------------------------
void Game::ReSpawn::OnEnter(const glm::vec2&)
{
	m_CurrentPos = m_StartPos - glm::vec2{ 0.f, m_SpawnHeight };
	m_OwnerObject->SetLocalPosition(m_CurrentPos);

	if (m_OwnerObject->CheckComponent<EggComponent>())
		m_OwnerObject->GetComponent<EggComponent>()->HatchEgg(false);

	if (m_OwnerObject->CheckComponent<TG::SpriteComponent>())
		m_OwnerObject->GetComponent<TG::SpriteComponent>()->UpdateFrame(1);

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
		OnExit();
		OnStateSwitch.OnNotifyAll(EState::idle);
	}
}

void Game::ReSpawn::OnExit()
{
	m_OwnerObject->ResetLife(m_gridPos);
}

//-----------------------------------------------

void Game::NPCReSpawn::Update(float time)
{
	if (m_CurrentTime < m_RespawnDelay)
	{
		m_CurrentTime += time;
		m_RespawnDelay = 1.f + rand() % 3;
		return;
	}

	const float fallSpeed{ 80.f };
	m_CurrentPos.y += fallSpeed * time;
	m_OwnerObject->SetLocalPosition(m_CurrentPos);

	if (TG::Transform::IsEqualVector(m_StartPos, m_CurrentPos, 1.f))
	{
		m_OwnerObject->SetLocalPosition(m_StartPos);
		m_CurrentTime = 0.f;
		OnExit();
		OnStateSwitch.OnNotifyAll(EState::idle);
	}
}

//----------------------------------------------------

void Game::WrongReSpawn::OnEnter(const glm::vec2&)
{
	m_CurrentPos = m_StartPos + glm::vec2{ 0.f, m_SpawnHeight };
	m_OwnerObject->SetLocalPosition(m_CurrentPos);

}

void Game::WrongReSpawn::Update(float time)
{
	if (m_CurrentTime < m_RespawnDelay)
	{
		m_CurrentTime += time;
		m_RespawnDelay = 1.f + rand() % 3;
		return;
	}

	const float fallSpeed{ 80.f };
	m_CurrentPos.y -= fallSpeed * time;
	m_OwnerObject->SetLocalPosition(m_CurrentPos);

	if (TG::Transform::IsEqualVector(m_StartPos, m_CurrentPos, 1.f))
	{
		m_OwnerObject->SetLocalPosition(m_StartPos);
		m_CurrentTime = 0.f;
		OnExit();
		OnStateSwitch.OnNotifyAll(EState::idle);
	}
}

//-------------------------------------------
//LIFT
//---------------------------------------------

void Game::Lift::OnEnter(const glm::vec2&)
{
	m_OwnerObject->JumpOfGrid(false);
}

void Game::Lift::OnExit()
{
	TG::Locator::getAudio().playSound("Disk Land");
}

#include "MenuState.h"
#include "SceneManager.h"
#include "Scene.h"


void TG::MenuState::UpdateGameMode(float Ydirection)
{
	int currentMode = static_cast<int>(m_GameMode);

	if (currentMode + Ydirection >= 2)
		m_GameMode = EGameMode::coop;
	else if (currentMode + Ydirection <= 0)
		m_GameMode = EGameMode::single;
	else
		m_GameMode = EGameMode::vs;
}

void TG::MenuState::IncreaseLvl(int lvl)
{
	OnStateSwitch.OnNotifyAll(EMenuState::intermediate, lvl);
}



//-----------------------------------------
//GAME
//-----------------------------------------
void TG::GameState::InputHandeling(const glm::vec2& signal)
{
	if (signal.x == 0 && signal.y == 0)
		OnStateSwitch.OnNotifyAll(EMenuState::pause, -1);
	
}
void TG::GameState::OnEnter()
{
	const int activeMode = m_OwnerObject->GetActiveGameModeIndex();

	m_ActiveScene->ActivateInput(true, activeMode);

	if (m_OwnerObject->GetPreviousMenuState() == EMenuState::pause)
		return;

	const int lvl = m_OwnerObject->GetCurrentLvl();
	m_ActiveScene->ApplyGameMode(activeMode, lvl);
}

void TG::GameState::Update(float dt)
{
	m_ActiveScene->Update(dt);
}

void TG::GameState::FixedUpdate(float dt)
{
	m_ActiveScene->FixedUpdate(dt);
}

void TG::GameState::OnExit()
{
	const int activeMode = m_OwnerObject->GetActiveGameModeIndex();
	m_ActiveScene->ActivateInput(false, activeMode);
}

//-----------------------------------------
//INTRO
//-----------------------------------------
void TG::IntroState::InputHandeling(const glm::vec2& signal)
{
	if (signal.x == 0 && signal.y == 0)
		OnStateSwitch.OnNotifyAll(EMenuState::selection,-1);
}


//-----------------------------------------
//SELECTION
//-----------------------------------------
void TG::SelectionState::InputHandeling(const glm::vec2& signal)
{
	//chose mode
	if (signal.x == 1 && signal.y != 0)
	{
		m_ActiveScene->GetGO(0)->HandleInput(signal);
		UpdateGameMode(signal.y);
	}

	// Enter
	//put lvl back to 1
	else if (signal.x == 0 && signal.y == 0)
		OnStateSwitch.OnNotifyAll(EMenuState::controls, 1);
}

void TG::SelectionState::OnExit()
{
	m_OwnerObject->UpdateGameMode(m_GameMode);
}


//-----------------------------------------
//CONTROL
//-----------------------------------------
void TG::ControlsState::InputHandeling(const glm::vec2& signal)
{
	if (signal.x == 0 && signal.y == 0)
		OnStateSwitch.OnNotifyAll(EMenuState::intermediate, -1);
}

void TG::ControlsState::OnEnter()
{
	const int activeMode = m_OwnerObject->GetActiveGameModeIndex();
	m_ActiveScene->ApplyGameMode(activeMode);
}

//-----------------------------------------
//INTERMEDIATE
//-----------------------------------------
void TG::IntermediateState::InputHandeling(const glm::vec2& signal)
{
	if (signal.x == 0 && signal.y == 0)
		OnStateSwitch.OnNotifyAll(EMenuState::game, -1);
}

void TG::IntermediateState::OnEnter()
{
	const int activeMode = m_OwnerObject->GetActiveGameModeIndex();
	const int lvl = m_OwnerObject->GetCurrentLvl();
	m_ActiveScene->ApplyGameMode(activeMode, lvl);
}

//-----------------------------------------
//PAUSE
//-----------------------------------------
void TG::PauseState::InputHandeling(const glm::vec2& signal)
{
	//Pressed ENTER
	if (signal.x == 0 && signal.y == 0)
		OnStateSwitch.OnNotifyAll(EMenuState::game, -1);

	//Pressed QUIT
	else if (signal.x == 1 && signal.y == 0)
	{
		OnStateSwitch.OnNotifyAll(EMenuState::selection, -1);
	}
}

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



//-----------------------------------------
//GAME
//-----------------------------------------
void TG::GameState::InputHandeling(const glm::vec2& signal)
{
	if (signal.x == 0 && signal.y == 0)
		OnStateSwitch.OnNotifyAll(EMenuState::pause);
	
}
void TG::GameState::OnEnter()
{
	const int activeMode = m_OwnerObject->GetActiveGameModeIndex();

	m_ActiveScene->ActivateInput(true, activeMode);

	if (m_OwnerObject->GetPreviousMenuState() == EMenuState::pause)
		return;

	m_ActiveScene->ApplyGameMode(activeMode);
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
		OnStateSwitch.OnNotifyAll(EMenuState::selection);
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
	else if (signal.x == 0 && signal.y == 0)
		OnStateSwitch.OnNotifyAll(EMenuState::controls);
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
		OnStateSwitch.OnNotifyAll(EMenuState::intermediate);
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
		OnStateSwitch.OnNotifyAll(EMenuState::game);
}

void TG::IntermediateState::OnEnter()
{
	const int activeMode = m_OwnerObject->GetActiveGameModeIndex();
	m_ActiveScene->ApplyGameMode(activeMode);
}

//-----------------------------------------
//PAUSE
//-----------------------------------------
void TG::PauseState::InputHandeling(const glm::vec2& signal)
{
	//Pressed ENTER
	if (signal.x == 0 && signal.y == 0)
		OnStateSwitch.OnNotifyAll(EMenuState::game);

	//Pressed QUIT
	else if (signal.x == 1 && signal.y == 0)
	{
		OnStateSwitch.OnNotifyAll(EMenuState::selection);
	}
}

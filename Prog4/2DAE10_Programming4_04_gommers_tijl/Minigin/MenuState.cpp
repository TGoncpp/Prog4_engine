#include "MenuState.h"
#include "SceneManager.h"
#include "Scene.h"

//-----------------------------------------
//GAME
//-----------------------------------------
void TG::GameState::InputHandeling(const glm::vec2& signal)
{
	if (signal.x == 0)
		OnStateSwitch.OnNotifyAll(EMenuState::pause);
	
} 

void TG::GameState::Update(float dt)
{
	m_ActiveScene->Update(dt);
}

void TG::GameState::FixedUpdate(float dt)
{
	m_ActiveScene->FixedUpdate(dt);
}

//-----------------------------------------
//INTRO
//-----------------------------------------
void TG::IntroState::InputHandeling(const glm::vec2& signal)
{
	if (signal.x == 0)
		OnStateSwitch.OnNotifyAll(EMenuState::selection);
}


//-----------------------------------------
//SELECTION
//-----------------------------------------
void TG::SelectionState::InputHandeling(const glm::vec2& signal)
{
	if (signal.x == 0)
		OnStateSwitch.OnNotifyAll(EMenuState::controls);
}

//-----------------------------------------
//CONTROL
//-----------------------------------------
void TG::ControlsState::InputHandeling(const glm::vec2& signal)
{
	if (signal.x == 0)
		OnStateSwitch.OnNotifyAll(EMenuState::intermediate);
}

//-----------------------------------------
//INTERMEDIATE
//-----------------------------------------
void TG::IntermediateState::InputHandeling(const glm::vec2& signal)
{
	if (signal.x == 0)
		OnStateSwitch.OnNotifyAll(EMenuState::game);
}

//-----------------------------------------
//PAUSE
//-----------------------------------------
void TG::PauseState::InputHandeling(const glm::vec2& signal)
{
	if (signal.x == 0)
		OnStateSwitch.OnNotifyAll(EMenuState::game);
	else if (signal.x == 1)
	{
		m_GameScenePtr->Reset();
		OnStateSwitch.OnNotifyAll(EMenuState::selection);
	}
}

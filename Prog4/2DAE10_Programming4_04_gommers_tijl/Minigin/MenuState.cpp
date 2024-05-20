#include "MenuState.h"
#include "SceneManager.h"
#include "Scene.h"

void TG::GameState::InputHandeling(const glm::vec2&)
{
	OnStateSwitch.OnNotifyAll(EMenuState::intro);
}

void TG::GameState::Update(float dt)
{
	m_ActiveScene->Update(dt);
}

void TG::GameState::FixedUpdate(float dt)
{
	m_ActiveScene->FixedUpdate(dt);
}

void TG::ControlsState::InputHandeling(const glm::vec2&)
{
	OnStateSwitch.OnNotifyAll(EMenuState::intermediate);
}

void TG::IntroState::InputHandeling(const glm::vec2&)
{
	OnStateSwitch.OnNotifyAll(EMenuState::intermediate);
}

void TG::IntroState::Update(float dt)
{
	m_ActiveScene->Update(dt);
}

void TG::SelectionState::InputHandeling(const glm::vec2&)
{
	OnStateSwitch.OnNotifyAll(EMenuState::intermediate);
}

void TG::IntermediateState::InputHandeling(const glm::vec2&)
{
	OnStateSwitch.OnNotifyAll(EMenuState::game);
}

void TG::IntermediateState::Update(float dt)
{
	m_ActiveScene->Update(dt);
}

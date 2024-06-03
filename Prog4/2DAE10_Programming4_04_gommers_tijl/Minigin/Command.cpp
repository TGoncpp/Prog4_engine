#include "Command.h"
#include "GameObject.h"
#include <iostream>
#include "scenemanager.h"
#include "serviceLocator.h"


TG::CommandActor::CommandActor(GameObject* gameObject)
	: Command(),
		m_GameObjectRefrence{nullptr},
		m_StoredGameObjectRefrence{gameObject}
{
	gameObject->OnActivateInput.AddObserver(this);
}

TG::CommandActor::~CommandActor()
{
	m_StoredGameObjectRefrence->OnActivateInput.RemoveObserver(this);
}

void TG::CommandActor::Notify(bool activate)
{
	Subscribe( activate);
}

void TG::CommandActor::Subscribe(bool activate)
{
	m_GameObjectRefrence = activate ? m_StoredGameObjectRefrence : nullptr;
}

void TG::Mute::Execute()
{
	m_IsMute = !m_IsMute;
	Locator::getAudio().MuteAllSounds(m_IsMute);
}

void TG::Move::Execute()
{
	if (!m_GameObjectRefrence)return;
	m_GameObjectRefrence->HandleInput(m_Direction);
}

void TG::Enter::Execute()
{
	SceneManager::GetInstance().GetInstance().HandleInput(glm::vec2{ 0.f, 0.f });
}

void TG::Quit::Execute()
{
	SceneManager::GetInstance().GetInstance().HandleInput(glm::vec2{ 1.f, 0.f });
}

void TG::MoveArrow::Execute()
{
	m_MoveUp ? SceneManager::GetInstance().GetInstance().HandleInput(glm::vec2{ 1.f, -1.f }) :
		SceneManager::GetInstance().GetInstance().HandleInput(glm::vec2{ 1.f, 1.f });
}

void TG::SkipLvl::Execute()
{

}

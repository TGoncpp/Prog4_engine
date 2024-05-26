#include "Command.h"
#include "GameObject.h"
#include <iostream>
#include "scenemanager.h"


TG::CommandActor::CommandActor(GameObject* gameObject)
	: Command(),
		m_GameObjectRefrence{gameObject}
{
}

void TG::Move::Execute()
{
	m_GameObjectRefrence->HandleInput(m_Direction);
}


void TG::Enter::Execute()
{
	SceneManager::GetInstance().GetInstance().HandleInput(glm::vec2{ 0.f, 0.f });
}

void TG::Quit::Execute()
{
	SceneManager::GetInstance().GetInstance().HandleInput(glm::vec2{ 1.f, 1.f });
}

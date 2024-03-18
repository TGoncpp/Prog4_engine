#include "Command.h"
#include "GameObject.h"
#include <iostream>


dae::CommandActor::CommandActor(GameObject* gameObject)
	: Command(),
		m_GameObjectRefrence{gameObject}
{
}

dae::GameObject* dae::CommandActor::GetGameObjRefrence() const
{
	return m_GameObjectRefrence;
}


void dae::MoveUp::Execute()
{

	m_MoveComp->UpdateMovement(m_Direction);

}


void dae::MoveDown::Execute()
{

	m_MoveComp->UpdateMovement(m_Direction);
}

void dae::MoveRight::Execute()
{

	m_MoveComp->UpdateMovement(m_Direction);
}

void dae::MoveLeft::Execute()
{

	m_MoveComp->UpdateMovement(m_Direction);
}

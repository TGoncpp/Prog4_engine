#include "Command.h"
#include "GameObject.h"
#include <iostream>


TG::CommandActor::CommandActor(GameObject* gameObject)
	: Command(),
		m_GameObjectRefrence{gameObject}
{
}

void TG::Move::Execute()
{
	m_GameObjectRefrence->HandleInput(m_Direction);
}

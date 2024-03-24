#include "Command.h"
#include "GameObject.h"
//#include "LootComponent.h"
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

dae::PickUp::PickUp(GameObject* target, const TG::LootType& type)
	:CommandActor(target),
	m_LootType{type}
{
}

void dae::PickUp::Execute()
{
	if (GetGameObjRefrence()->CheckComponent<TG::LootComponent>())
		GetGameObjRefrence()->GetComponent<TG::LootComponent>()->PickupLoot(m_LootType);
}

dae::Hit::Hit(GameObject* target, GameObject* hitTarget)
	:CommandActor{target},
	m_HitTarget{hitTarget}
{
}

void dae::Hit::Execute()
{

}

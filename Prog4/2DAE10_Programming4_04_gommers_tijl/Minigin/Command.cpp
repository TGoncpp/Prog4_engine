#include "Command.h"
#include "GameObject.h"
#include "HealthComponent.h"
//#include "LootComponent.h"
#include <iostream>


TG::CommandActor::CommandActor(GameObject* gameObject)
	: Command(),
		m_GameObjectRefrence{gameObject}
{
}

void TG::Move::Execute()
{
	m_MoveComp->SetTargetLocation(m_Direction);
}


TG::PickUp::PickUp(GameObject* target, const TG::LootType& type)
	:CommandActor(target),
	m_LootType{type}
{
}

void TG::PickUp::Execute()
{
	if (m_GameObjectRefrence->CheckComponent<TG::LootComponent>())
		m_GameObjectRefrence->GetComponent<TG::LootComponent>()->PickupLoot(m_LootType);
}

TG::Hit::Hit(GameObject* target, GameObject* hitTarget)
	:CommandActor{target},
	m_HitTarget{hitTarget}
{
}

void TG::Hit::Execute()
{
	m_HitTarget->GetComponent<TG::HealthComponent>()->DecreaseHealth(1);
}

#pragma once
#include "windows.h"
#include "glm/vec2.hpp"
#include "MovementComponent.h"
#include "LootComponent.h"
#include "GameObject.h"


namespace TG
{
	class GameObject;

	class Command
	{
	public:
		virtual ~Command() = default;
		virtual void Execute() = 0;
	};

	class CommandActor : public Command
	{
	public:
		CommandActor(GameObject* gameObject);
		virtual ~CommandActor()override = default;

	protected:
		GameObject* m_GameObjectRefrence = nullptr;

	};


	class Move final : public CommandActor
	{
	public:
		Move(GameObject* Objectrefrence, const glm::vec2& direction)
			: CommandActor(Objectrefrence),
			m_Direction{direction}
		{
			m_MoveComp = m_GameObjectRefrence->GetComponent<TG::MovementComponent>();
		};
		~Move() = default;
		virtual void Execute()override;
	protected:
		TG::MovementComponent* m_MoveComp = nullptr;
		glm::vec2 m_Direction{ glm::vec2{0.f, 0.f} };
	};


	//enum class TG::LootType;
	class PickUp final : public CommandActor
	{
	public:
		PickUp(GameObject* target, const TG::LootType& type);
		virtual ~PickUp() = default;
		virtual void Execute() override;
	private:
		TG::LootType m_LootType;

	};

	class Hit final : public CommandActor
	{
	public:
		Hit(GameObject* target, GameObject* hitTarget);
		virtual ~Hit() = default;
		virtual void Execute() override;

	private:
		GameObject* m_HitTarget;
	};


	

}
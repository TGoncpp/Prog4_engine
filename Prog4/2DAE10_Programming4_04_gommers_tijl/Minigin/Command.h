#pragma once
#include "windows.h"
//#include "Xinput.h"
#include "glm/vec2.hpp"
#include "MovementComponent.h"
#include "LootComponent.h"
#include "GameObject.h"


namespace dae
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
		GameObject* GetGameObjRefrence()const;

	private:
		GameObject* m_GameObjectRefrence = nullptr;
	};


	class Move  : public CommandActor
	{
	public:
		Move(GameObject* Objectrefrence)
			: CommandActor(Objectrefrence)
		{
			m_MoveComp = GetGameObjRefrence()->GetComponent<TG::MovementComponent>();
		};
		~Move() = default;
		virtual void Execute()override = 0;
	protected:
		TG::MovementComponent* m_MoveComp = nullptr;

	};

	class MoveUp final : public Move
	{
	public:
		MoveUp(GameObject* Objectrefrence)
			: Move(Objectrefrence) {};
		~MoveUp() = default;
		virtual void Execute()override;
	private:
		glm::vec2 m_Direction{0.f, -1.f};
	};

	class MoveDown final : public Move
	{
	public:
		MoveDown(GameObject * Objectrefrence)
		: Move(Objectrefrence) {};
		~MoveDown() = default;
		virtual void Execute()override;
	private:
		glm::vec2 m_Direction{0.f, 1.f};
	};

	class MoveRight final : public Move
	{
	public:
		MoveRight(GameObject * Objectrefrence)
		: Move(Objectrefrence) {};
		~MoveRight() = default;
		virtual void Execute()override;
	private:
		glm::vec2 m_Direction{1.f, 0.f};
	};

	class MoveLeft final : public Move
	{
	public:
		MoveLeft(GameObject * Objectrefrence)
		: Move(Objectrefrence) {};
		~MoveLeft() = default;
		virtual void Execute()override;
	private:
		glm::vec2 m_Direction{-1.f, 0.f};
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
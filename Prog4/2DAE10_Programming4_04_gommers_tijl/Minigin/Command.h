#pragma once
#include "windows.h"
#include "glm/vec2.hpp"
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
			m_Direction{direction}{}
		
		~Move() = default;
		virtual void Execute()override;
	protected:
		glm::vec2 m_Direction{ glm::vec2{0.f, 0.f} };
	};
	
	class Enter final : public CommandActor
	{
	public:
		Enter(GameObject* Objectrefrence)
			: CommandActor(Objectrefrence)
			{}
		
		~Enter() = default;
		virtual void Execute()override;
	
	};
	
	class Quit final : public CommandActor
	{
	public:
		Quit(GameObject* Objectrefrence)
			: CommandActor(Objectrefrence)
			{}
		
		~Quit() = default;
		virtual void Execute()override;
	
	};
	
	class MoveArrow final : public CommandActor
	{
	public:
		MoveArrow(GameObject* Objectrefrence, bool isUp)
			: CommandActor(Objectrefrence),
			m_MoveUp{isUp}
			{}
		
		~MoveArrow() = default;
		virtual void Execute()override;
	private:
		bool m_MoveUp{ };
	};

}
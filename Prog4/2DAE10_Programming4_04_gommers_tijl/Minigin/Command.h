#pragma once
#include "windows.h"
#include "glm/vec2.hpp"
#include "GameObject.h"
#include "subject.h"


namespace TG
{
	class GameObject;

	class Command
	{
	public:
		virtual ~Command() = default;
		virtual void Execute() = 0;
	};

	class CommandActor : public Command, public IObserver<bool>
	{
	public:
		CommandActor(GameObject* gameObject);
		virtual ~CommandActor()override;
		virtual void Notify(bool activate)override;
		virtual void OnSubjectDestroy()override {};

	protected:
		GameObject* m_GameObjectRefrence       = nullptr;
		GameObject* m_StoredGameObjectRefrence = nullptr;

		virtual void Subscribe(bool activate);
	};


	class Mute : public Command
	{
	public:
		Mute() = default;
		virtual ~Mute()override = default;

		virtual void Execute()override;
	private:
		bool m_IsMute{ false };
	};
	
	class Move final : public CommandActor
	{
	public:
		Move(GameObject* Objectrefrence, const glm::vec2& direction)
			: CommandActor(Objectrefrence),
			m_Direction{direction}{}
		
		virtual void Execute()override;
	protected:
		glm::vec2 m_Direction{ glm::vec2{0.f, 0.f} };
	};
	
	class SkipLvl final: public CommandActor
	{
	public:
		SkipLvl(GameObject* Objectrefrence)
		: CommandActor(Objectrefrence)
			{}
		virtual ~SkipLvl()override = default;

		virtual void Execute()override;
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
	
	class ChangeLetter final : public CommandActor
	{
	public:
		ChangeLetter(GameObject* Objectrefrence, const glm::vec2& signal)
			: CommandActor(Objectrefrence),
			m_Signal{signal}
			{}
		
		~ChangeLetter() = default;
		virtual void Execute()override;
	private:
		glm::vec2 m_Signal{ };
	};
	
	
}
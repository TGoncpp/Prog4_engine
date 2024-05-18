#pragma once
#include <glm/glm.hpp>
#include <spriteComponent.h>
#include <subject.h>

namespace Game
{
	class Character;
	//-----------------------------------------
	//INTERFACE
	//---------------------------------------
	enum class EState
	{
		idle,
		walking,
		falling,
		dead,
		respawn,
		lift//only for red character
	};

	class IState
	{
	public:
		IState(Character* owner)
			:m_OwnerObject{owner}{}
		
		void virtual InputHandeling(const glm::vec2& ) = 0;
		void virtual OnEnter(const glm::vec2&) = 0;
		void virtual Update(float) = 0;
		void virtual FixedUpdate(float) = 0;
		void virtual OnExit() = 0;
		TG::Subject<const EState&> OnStateSwitch{};
	protected:

		Character* m_OwnerObject{};
	};

	//-----------------------------------------
	//STATES
	//-----------------------------------------
	class State : public IState
	{
	public:
		State(Character* owner);
		
		void virtual InputHandeling(const glm::vec2&) {};
		void virtual OnEnter(const glm::vec2&){};
		void virtual Update(float){};
		void virtual FixedUpdate(float){};
		void virtual OnExit(){};

		EState GetState()const { return m_Type; }
	protected:
		EState m_Type{ };
	};

	//WALKING
	//---------------------------------------
	class MovementComponent;
	class WalkingState : public State
	{
	public:
		WalkingState(Character* owner);
		void virtual InputHandeling(const glm::vec2& )override {};
		void virtual OnEnter(const glm::vec2&)override{};
		void virtual Update(float)override {};
		void virtual FixedUpdate(float)override {};
		void virtual OnExit()override{};
	protected:
		MovementComponent* m_MoveComp{};
		TG::SpriteComponent* m_SpriteComp{};
	};

	class WalkingQbertState : public WalkingState
	{
	public:
		WalkingQbertState(Character* owner)
			:WalkingState(owner) {}
		void virtual InputHandeling(const glm::vec2&)override ;
		void virtual OnEnter(const glm::vec2&)override ;
		void virtual Update(float)override;
		void virtual FixedUpdate(float)override;
		void virtual OnExit()override ;

	};
	
	//IDLE
	//---------------------------------------
	class Idle : public State
	{
	public:
		Idle(Character* owner)
			:State(owner) 
		{
			m_Type = EState::idle ;
		}
		void virtual InputHandeling(const glm::vec2& direction)override ;
		void virtual OnEnter(const glm::vec2&)override{};
		void virtual Update(float)override;
		void virtual OnExit()override{};

	};

	//LIFT
	//---------------------------------------
	class Lift : public State
	{
	public:
		Lift(Character* owner)
			:State(owner) 
		{
			m_Type = EState::lift ;
		}
		void virtual OnEnter(const glm::vec2&)override;
		void virtual OnExit()override{};
	};
	
	//DEAD
	//---------------------------------------
	class Dead : public State
	{
	public:
		Dead(Character* owner, float timeToDie)
			:State(owner), m_TimeToDie{ timeToDie } 
		{
			m_Type = EState::dead ;
		}
		void virtual InputHandeling(const glm::vec2&)override {};
		void virtual OnEnter(const glm::vec2&)override ;
		void virtual Update(float)override ;
		void virtual OnExit()override {};
	protected:
		const float m_TimeToDie{};
		float m_CurrentDieTime{};
	};

	class GreenDead : public Dead
	{
	public:
		GreenDead(Character* owner, float timeToDie)
			:Dead(owner, timeToDie) {}
		void virtual OnEnter(const glm::vec2&)override ;
	
	};

	//FALLING
	//---------------------------------------
	class Falling : public State
	{
	public:
		Falling(Character* owner, float fallTime)
			:State(owner), m_FallTime{ fallTime } 
		{
			m_Type = EState::falling;
		}
		void virtual InputHandeling(const glm::vec2& )override {};
		void virtual OnEnter(const glm::vec2&)override ;
		void virtual Update(float)override ;
		void virtual OnExit()override {};
	private:
		glm::vec2 m_FallPosition;
		glm::vec2 m_CurrentFallPosition;
		const float m_FallTime{};
		float m_CurrentFallTime{};
	};

	//RESPAWN
	//---------------------------------------
	class ReSpawn : public State
	{
	public:
		ReSpawn(Character* owner, const glm::vec2& startPosition, float respawnHeight)
			:State(owner),
			m_StartPos{ startPosition },
			m_SpawnHeight{ respawnHeight } 
		{
			m_Type = EState::respawn;
		}
		void virtual InputHandeling(const glm::vec2& )override {};
		void virtual OnEnter(const glm::vec2&)override ;
		void virtual Update(float)override ;
		void virtual OnExit()override ;
	private:
		const glm::vec2 m_StartPos;
		glm::vec2 m_CurrentPos;
		const float m_SpawnHeight{};
	};
}
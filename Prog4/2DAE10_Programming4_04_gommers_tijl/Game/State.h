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
		lift,//only for red character,
		dissable,
		freeze
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
		TG::Subject<bool> OnShowCurse;

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

	class WalkingQbertState final: public WalkingState
	{
	public:
		WalkingQbertState(Character* owner)
			:WalkingState(owner) {}
		void virtual InputHandeling(const glm::vec2&)override ;
		void virtual OnEnter(const glm::vec2&)override ;
		void virtual FixedUpdate(float)override;

	};

	class WalkingGreenState final: public WalkingState
	{
	public:
		WalkingGreenState(Character* owner, bool isSam)
			:WalkingState(owner),
			m_IsSam{isSam} {}
		void virtual OnEnter(const glm::vec2&)override;
		void virtual FixedUpdate(float)override ;

	private:
		//is bool for setting which off the 2 green characters is used
		bool m_IsSam{ false };
	
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

	class GreenIdle final: public Idle
	{
	public:
		GreenIdle(Character* owner, float idleTime)
			:Idle(owner),
			m_Idletime{idleTime} {}
		void virtual InputHandeling(const glm::vec2& )override {};
		void virtual OnEnter(const glm::vec2&)override;
		void virtual Update(float)override ;
	private:
		glm::vec2 m_Direction;
		const float m_Idletime{ 1.f };
		float m_CurrentIdletime{  };
	};

	//LIFT
	//---------------------------------------
	class Lift final: public State
	{
	public:
		Lift(Character* owner)
			:State(owner) 
		{
			m_Type = EState::lift ;
		}
		void virtual OnEnter(const glm::vec2&)override;
		void virtual OnExit()override;
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
		void virtual OnExit()override ;
	protected:
		const float m_TimeToDie{};
		float m_CurrentDieTime{};
	};

	class GreenDead final: public Dead
	{
	public:
		GreenDead(Character* owner, float timeToDie)
			:Dead(owner, timeToDie) {}
		void virtual OnEnter(const glm::vec2&)override ;
	
	};
	
	class PurpleDead final: public Dead
	{
	public:
		PurpleDead(Character* owner, float timeToDie)
			:Dead(owner, timeToDie) {}
		void virtual OnEnter(const glm::vec2&)override ;
	
	};

	//FALLING
	//---------------------------------------
	class Falling final: public State
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

	protected:
		const glm::vec2 m_StartPos;
		glm::vec2 m_CurrentPos;
		std::pair<int, int> m_gridPos{std::make_pair(0,0)};
		const float m_SpawnHeight{};
	};

	class NPCReSpawn final: public ReSpawn
	{
	public:
		NPCReSpawn(Character* owner, const glm::vec2& startPosition, float respawnHeight, float respawnDelay, std::pair<int, int> gridStartPos)
			:ReSpawn(owner, startPosition, respawnHeight),
			m_RespawnDelay{respawnDelay} 
		{
			m_gridPos = gridStartPos ;
		}
		void virtual Update(float)override ;

	private:
		const float m_RespawnDelay{};
		float m_CurrentTime{};
	};


	//DISSABLE
	//---------------------------------------
	class Dissable final: public State
	{
	public:
		Dissable(Character* owner)
			:State(owner)
		{
			m_Type = EState::dissable;
		}

	};

	//FREEZE
	//---------------------------------------
	class Freeze final: public State
	{
	public:
		Freeze(Character* owner)
			:State(owner)
		{
			m_Type = EState::freeze;
		}

	};
}
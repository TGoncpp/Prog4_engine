#pragma once
#include <glm/glm.hpp>

namespace Game
{
	class Character;
	//-----------------------------------------
	//INTERFACE
	//---------------------------------------
	class IState
	{
	public:
		IState(Character* owner)
			:m_OwnerObject{owner}{}
		
		void virtual InputHandeling(const glm::vec2& ) = 0;
		void virtual OnEnter(const glm::vec2&) = 0;
		void virtual Update(float) = 0;
		void virtual OnExit() = 0;
	protected:

		Character* m_OwnerObject{};
	};

	//-----------------------------------------
	//STATES
	//---------------------------------------
	class State : public IState
	{
	public:
		State(Character* owner)
			:IState{owner}{}
		
		void virtual InputHandeling(const glm::vec2&) {};
		void virtual OnEnter(const glm::vec2&){};
		void virtual Update(float){};
		void virtual OnExit(){};

	};

	class WalkingState : public State
	{
	public:
		WalkingState(Character* owner)
			:State(owner) {}
		void virtual InputHandeling(const glm::vec2& )override {};
		void virtual OnEnter(const glm::vec2&)override{};
		void virtual Update(float)override;
		void virtual OnExit()override{};

	};
	
	class Idle : public State
	{
	public:
		Idle(Character* owner)
			:State(owner) {}
		void virtual InputHandeling(const glm::vec2& direction)override ;
		void virtual OnEnter(const glm::vec2&)override{};
		void virtual Update(float)override;
		void virtual OnExit()override{};
	};

	class WalkingQbertState : public WalkingState
	{
	public:
		WalkingQbertState(Character* owner)
			:WalkingState(owner) {}
		void virtual InputHandeling(const glm::vec2&)override ;
		void virtual OnEnter(const glm::vec2&)override ;
		void virtual Update(float)override;
		void virtual OnExit()override ;
	};
	
	class Dead : public State
	{
	public:
		Dead(Character* owner, float timeToDie)
			:State(owner), m_TimeToDie{ timeToDie } {}
		void virtual InputHandeling(const glm::vec2&)override {};
		void virtual OnEnter(const glm::vec2&)override ;
		void virtual Update(float)override ;
		void virtual OnExit()override {};
	private:
		const float m_TimeToDie{};
		float m_CurrentDieTime{};
	};

	class Falling : public State
	{
	public:
		Falling(Character* owner, float fallTime)
			:State(owner), m_FallTime{ fallTime } {}
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

	class ReSpawn : public State
	{
	public:
		ReSpawn(Character* owner, const glm::vec2& startPosition, float respawnHeight)
			:State(owner), 
			m_StartPos{ startPosition },
			m_SpawnHeight{ respawnHeight } {}
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
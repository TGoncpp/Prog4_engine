#pragma once
#include <glm/glm.hpp>
#include "GameObject.h"

//class TG::GameObject;
namespace Game
{
	//-----------------------------------------
	//INTERFACE
	//---------------------------------------
	class IState
	{
	public:
		IState(TG::GameObject* owner)
			:m_OwnerObject{owner}{}
		
		void virtual InputHandeling(const glm::vec2& ) = 0;
		void virtual OnEnter(const glm::vec2&) = 0;
		void virtual Update(float) = 0;
		void virtual OnExit() = 0;
	protected:

		TG::GameObject* m_OwnerObject{};
	};

	//-----------------------------------------
	//STATES
	//---------------------------------------
	class State : public IState
	{
	public:
		State(TG::GameObject* owner)
			:IState{owner}{}
		
		void virtual InputHandeling(const glm::vec2&) {};
		void virtual OnEnter(const glm::vec2&){};
		void virtual Update(float){};
		void virtual OnExit(){};

	};

	class WalkingState : public State
	{
	public:
		WalkingState(TG::GameObject* owner)
			:State(owner) {}
		void virtual InputHandeling(const glm::vec2& )override {};
		void virtual OnEnter(const glm::vec2&)override{};
		void virtual Update(float)override;
		void virtual OnExit()override{};

	};
	
	class Idle : public State
	{
	public:
		Idle(TG::GameObject* owner)
			:State(owner) {}
		void virtual InputHandeling(const glm::vec2& direction)override ;
		void virtual OnEnter(const glm::vec2&)override{};
		void virtual Update(float)override{};
		void virtual OnExit()override{};
	};

	class WalkingQbertState : public WalkingState
	{
	public:
		WalkingQbertState(TG::GameObject* owner)
			:WalkingState(owner) {}
		void virtual InputHandeling(const glm::vec2& )override ;
		void virtual OnEnter(const glm::vec2&)override;
		void virtual Update(float)override;
		void virtual OnExit()override;
	};
}
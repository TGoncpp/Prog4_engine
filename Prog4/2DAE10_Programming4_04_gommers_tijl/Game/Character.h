#pragma once
#include "GameObject.h"
#include "State.h"
#include "subject.h"
#include <map>

namespace Game
{
	class IState;
	enum class ECharacterType
	{
		green  = 0, 
		red    = 1, 
		purple = 2

	};
	
	class Character : public TG::GameObject, public TG::IObserver<const EState&>
	{
	public:
		Character(const glm::vec2& position, std::shared_ptr<TG::Texture2D> textureSPTR, const glm::vec2& jumpOffset);
		Character()                            = default;
		~Character()                           = default;
		Character& operator=(const Character&) = delete;
		Character& operator=(Character&&)      = delete;
		Character(const Character&)            = delete;
		Character(Character&&)                 = delete;

		//GameObject
		virtual void HandleInput(const glm::vec2& direction)override;
		virtual void Update(float time)override;
		virtual void FixedUpdate(float)override ;

		void UpdateGrid(bool isMoving);
		//void NewState(const EState& newState);
		void SetDirection(const glm::vec2& newDirection);
		void UpdateGridPosition(const glm::vec2& direction);

		TG::Subject<Character*, bool> OnCubeInteraction;
		void SetPositionOnGridByIndex(int toLeft, int ToBelow, const glm::vec2& jumpOffset);
		void CollisionCheck(const ECharacterType& dominantType, std::pair<int, int> GridPostion);
		void JumpOfGrid();
		void ResetLife();

		//Getters
		std::pair<int, int> GetGridPosition()const { return m_GridPostion; }
		ECharacterType GetCharacterType()const     { return m_Type;}
		bool IsDead()const                         { return m_IsDead; }
		bool IsFalling()const                      { return m_IsFalling; }

	protected:

		glm::vec2 m_Direction{};
		ECharacterType m_Type{ ECharacterType::red };
		std::map <EState ,std::unique_ptr<State>> m_PossibleStates;
		State* m_CharacterState{ nullptr };

	private:
		std::pair<int, int> m_GridPostion;
		int m_Health{ 3 };
		int m_Score{ 0 };
		bool m_IsDead{ false };
		bool m_IsFalling{ false };

		//IObserver
		virtual void Notify(const EState&)override;
		virtual void OnSubjectDestroy()override;

		void SetCharacterType(const ECharacterType& newType);
	};
}
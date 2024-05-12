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
	
	class Character : public TG::GameObject
	{
	public:
		Character(const glm::vec2& position, std::shared_ptr<TG::Texture2D> textureSPTR, const glm::vec2& jumpOffset, int gridSizent, std::pair<int, int> spriteSheet);
		Character()                            = default;
		~Character()                           = default;
		Character& operator=(const Character&) = delete;
		Character& operator=(Character&&)      = delete;
		Character(const Character&)            = delete;
		Character(Character&&)                 = delete;

		virtual bool UpdateGridPosition(const glm::vec2& direction) override;
		virtual void UpdateGrid(bool isMoving) override;
		virtual void HandleInput(const glm::vec2& direction)override;
		virtual void NewState(const std::string& newState);
		virtual void Update(float time)override;
		virtual void SetDirection(const glm::vec2& newDirection);


		//TG::Subject<std::pair<int, int>, ECharacterType, bool> OnCubeInteraction;
		TG::Subject<Character*, bool> OnCubeInteraction;
		void SetPositionOnGridByIndex(int toLeft, int ToBelow, const glm::vec2& jumpOffset);
		void CollisionCheck(const ECharacterType& dominantType, std::pair<int, int> GridPostion);

		std::pair<int, int> GetGridPosition()const;
		ECharacterType GetCharacterType()const {return m_Type;};

	protected:
		glm::vec2 m_Direction{};
		ECharacterType m_Type{ ECharacterType::red };

	private:
		std::map <std::string ,std::unique_ptr<State>> m_PossibleStates;
		State* m_CharacterState{ nullptr };
		std::pair<int, int> m_GridPostion;
		int m_Health{ 3 };
		int m_Score{ 0 };

		void SetCharacterType(const ECharacterType& newType);
	};
}
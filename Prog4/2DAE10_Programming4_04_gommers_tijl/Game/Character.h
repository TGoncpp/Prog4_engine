#pragma once
#include "GameObject.h"
#include "subject.h"

namespace Game
{
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

		virtual void SetState(const glm::vec2& direction) override;
		virtual void UpdateGrid(bool isMoving) override;
		TG::Subject<std::pair<int, int>, ECharacterType, bool> OnCubeInteraction;
		void SetPositionOnGridByIndex(int toLeft, int ToBelow, const glm::vec2& jumpOffset);
		void CollisionCheck(const ECharacterType& dominantType, std::pair<int, int> GridPostion);

	protected:
		ECharacterType m_Type{ ECharacterType::red };

	private:
		std::pair<int, int> m_GridPostion;
		int m_Health{ 3 };
		int m_Score{ 0 };

		void SetCharacterType(const ECharacterType& newType);
	};
}
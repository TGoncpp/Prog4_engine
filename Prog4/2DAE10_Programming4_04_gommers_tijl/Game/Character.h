#pragma once
#include "GameObject.h"

namespace Game
{
	enum class CharacterState
	{
		leftdown,
		leftUp,
		rightDown,
		rightUp
	};

	class Character : public TG::GameObject
	{
		Character(const glm::vec2& position, std::shared_ptr<TG::Texture2D> texuteSPTR);
		Character()                            = default;
		~Character()                           = default;
		Character& operator=(const Character&) = delete;
		Character& operator=(Character&&)      = delete;
		Character(const Character&)            = delete;
		Character(Character&&)                 = delete;



	private:
		CharacterState m_State{ CharacterState::leftdown };

		void UpdateState(const glm::vec2& direction);
	};
}
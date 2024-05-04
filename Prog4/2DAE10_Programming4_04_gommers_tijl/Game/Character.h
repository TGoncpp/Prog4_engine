#pragma once
#include "GameObject.h"
#include "subject.h"

namespace Game
{
	
	class Character : public TG::GameObject
	{
	public:
		Character(const glm::vec2& position, std::shared_ptr<TG::Texture2D> texuteSPTR, const glm::vec2& jumpOffset, int gridSizent);
		Character()                            = default;
		~Character()                           = default;
		Character& operator=(const Character&) = delete;
		Character& operator=(Character&&)      = delete;
		Character(const Character&)            = delete;
		Character(Character&&)                 = delete;

		virtual void SetState(const glm::vec2& direction) override;
		virtual void UpdateGrid() override;
		TG::Subject<std::pair<int, int>> OnCubeInteraction;

	private:
		std::pair<int, int> m_GridPostion;
	};
}
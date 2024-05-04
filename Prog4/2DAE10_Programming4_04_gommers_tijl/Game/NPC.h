#pragma once
#include "Character.h"

namespace Game 
{

	class NPC : public Character
	{
	public:
		NPC(const glm::vec2& position, std::shared_ptr<TG::Texture2D> texuteSPTR, const glm::vec2& jumpOffset, int gridSizent, std::pair<int, int> spriteSheet);
		NPC() = default;
		~NPC() = default;
		NPC& operator=(const NPC&) = delete;
		NPC& operator=(NPC&&) = delete;
		NPC(const NPC&) = delete;
		NPC(NPC&&) = delete;

		
	private:

	};
}
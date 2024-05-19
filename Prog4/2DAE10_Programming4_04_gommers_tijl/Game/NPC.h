#pragma once
#include "Character.h"

namespace Game 
{

	class NPC final : public Character
	{
	public:
		NPC(const glm::vec2& position, std::shared_ptr<TG::Texture2D> texuteSPTR, const glm::vec2& jumpOffset, const ECharacterType& type);
		NPC() = default;
		~NPC() = default;
		NPC& operator=(const NPC&) = delete;
		NPC& operator=(NPC&&) = delete;
		NPC(const NPC&) = delete;
		NPC(NPC&&) = delete;

		
	private:

	};
}
#include "NPC.h"
#include "spriteComponent.h"

Game::NPC::NPC(const glm::vec2& position, std::shared_ptr<TG::Texture2D> texuteSPTR, const glm::vec2& jumpOffset, int gridSize, std::pair<int, int> spriteSheet, const ECharacterType& type)
	:Character(position, texuteSPTR, jumpOffset, gridSize, spriteSheet)
{	
	if (CheckComponent<TG::SpriteComponent>())
		GetComponent<TG::SpriteComponent>()->UpdateFrame(1);
	m_Type = type;
}

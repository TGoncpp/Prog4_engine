#include "NPC.h"
#include "spriteComponent.h"

Game::NPC::NPC(const glm::vec2& position, std::shared_ptr<TG::Texture2D> texuteSPTR, const glm::vec2& jumpOffset, const ECharacterType& type)
	:Character(position, texuteSPTR, jumpOffset)
{	
	if (CheckComponent<TG::SpriteComponent>())
		GetComponent<TG::SpriteComponent>()->UpdateFrame(1);
	m_Type = type;

	if (m_Type == ECharacterType::green)
	{
		m_PossibleStates[EState::lift]->OnStateSwitch.RemoveObserver(this);
		m_PossibleStates[EState::lift] = nullptr;
		m_PossibleStates[EState::dead] = std::make_unique<GreenDead>(this, 1.f);
		m_PossibleStates[EState::dead]->OnStateSwitch.AddObserver(this);
	}
}

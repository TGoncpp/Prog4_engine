#include "NPC.h"
#include "spriteComponent.h"
#include "sceneManager.h"
#include "player2Component.h"

Game::NPC::NPC(const glm::vec2& position, std::shared_ptr<TG::Texture2D> texuteSPTR, const glm::vec2& jumpOffset, const ECharacterType& type)
	:Character(position, texuteSPTR, jumpOffset)
{	
	if (CheckComponent<TG::SpriteComponent>())
		GetComponent<TG::SpriteComponent>()->UpdateFrame(1);
	m_Type = type;

	if (m_Type == ECharacterType::green)
	{
		m_PossibleStates[EState::dead] = std::make_unique<GreenDead>(this, 1.f);
		m_PossibleStates[EState::dead]->OnStateSwitch.AddObserver(this);
	}
	else if (m_Type == ECharacterType::purple)
	{
		m_PossibleStates[EState::dead] = std::make_unique<PurpleDead>(this, 1.f);
		m_PossibleStates[EState::dead]->OnStateSwitch.AddObserver(this);
	}
	

}

void Game::NPC::ApplyGameMode(int gameMode, int)
{
	TG::EGameMode mode = static_cast<TG::EGameMode>(gameMode);

	if (CheckComponent<Player2Component>())
	{
		if (mode == TG::EGameMode::vs)
		{
			SetPositionOnGridByIndex(6, 0, m_JumpOffset);
			m_CharacterState = m_PossibleStates[EState::idle].get();
		}

		else
		{
			SetPositionOnGridByIndex(12, 0, m_JumpOffset);
			m_CharacterState = m_PossibleStates[EState::dissable].get();
		}
	}
	else
		m_CharacterState = m_PossibleStates[EState::dissable].get();

}

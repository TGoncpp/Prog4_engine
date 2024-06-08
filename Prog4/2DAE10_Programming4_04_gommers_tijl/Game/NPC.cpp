#include "NPC.h"
#include "spriteComponent.h"
#include "sceneManager.h"
#include "player2Component.h"

Game::NPC::NPC(const glm::vec2& position, std::shared_ptr<TG::Texture2D> texuteSPTR, const glm::vec2& jumpOffset, const ECharacterType& type, bool isType2)
	:Character(position, texuteSPTR, jumpOffset)
{	
	TG::SpriteComponent* spriteComp = nullptr;
	if (CheckComponent<TG::SpriteComponent>())
	{
		spriteComp = GetComponent<TG::SpriteComponent>();
		spriteComp->UpdateFrame(1);
		assert("no spritecomponent found in npc class");
	}
	m_Type = type;

	std::pair<int, int>gridStartPos = isType2? std::make_pair(1, 0) : std::make_pair(0, 1);
	glm::vec2 startPos = TG::Transform::CalculateGridPosition(gridStartPos.first, gridStartPos.second, jumpOffset, m_ZeroPosition);
	
	if (m_Type == ECharacterType::green)
	{

		const float DieTime{ 0.4f };
		m_PossibleStates[EState::dead] = std::make_unique<GreenDead>(this, DieTime);
		m_PossibleStates[EState::dead]->OnStateSwitch.AddObserver(this);
	
		const float idleTime{ 1.f };
		m_PossibleStates[EState::idle] = std::make_unique<GreenIdle>(this, idleTime);
		m_PossibleStates[EState::idle]->OnStateSwitch.AddObserver(this);

		m_PossibleStates[EState::walking] = std::make_unique<WalkingGreenState>(this, isType2);
		m_PossibleStates[EState::walking]->OnStateSwitch.AddObserver(this);

		int frame = isType2 ? 1 : 3;
		spriteComp->UpdateFrame(frame);

	}
	else if (m_Type == ECharacterType::purple)
	{
		const float DieTime{ 1.f };
		m_PossibleStates[EState::dead] = std::make_unique<PurpleDead>(this, DieTime);
		m_PossibleStates[EState::dead]->OnStateSwitch.AddObserver(this);
	}
	
	const float spawnHeight{ 200.f };
	const float spawnDelay{ 1.f  + rand()% 3 };
	m_PossibleStates[EState::respawn] = std::make_unique<NPCReSpawn>(this, startPos, spawnHeight, spawnDelay, gridStartPos);
	m_PossibleStates[EState::respawn]->OnStateSwitch.AddObserver(this);
	
	

}

void Game::NPC::ApplyGameMode(int gameMode, int )
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
		m_CharacterState = m_PossibleStates[EState::dead].get();

}

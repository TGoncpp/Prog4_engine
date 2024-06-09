#include "NPC.h"
#include "spriteComponent.h"
#include "sceneManager.h"
#include "player2Component.h"
#include "eggComponent.h"
#include "movementComponent.h"

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
		const float DieTime{ 0.5f };
		m_PossibleStates[EState::dead] = std::make_unique<PurpleDead>(this, DieTime);
		m_PossibleStates[EState::dead]->OnStateSwitch.AddObserver(this);

		const float idleTime{ 1.f };
		m_PossibleStates[EState::idle] = std::make_unique<CoilyIdle>(this, idleTime);
		m_PossibleStates[EState::idle]->OnStateSwitch.AddObserver(this);

		float heigthOfLowestCube{ TG::Transform::CalculateGridPosition(6 ,0, jumpOffset, m_ZeroPosition).y };
		m_PossibleStates[EState::walking] = std::make_unique<WalkingCoilynState>(this, heigthOfLowestCube);
		m_PossibleStates[EState::walking]->OnStateSwitch.AddObserver(this);

		spriteComp->UpdateFrame(1);

		gridStartPos = std::make_pair(0, 0);
	}

	glm::vec2 startPos = TG::Transform::CalculateGridPosition(gridStartPos.first, gridStartPos.second, jumpOffset, m_ZeroPosition);

	const float spawnHeight{ 200.f };
	const float spawnDelay{ 4.5f  + rand()% 4 };
	m_PossibleStates[EState::respawn] = std::make_unique<NPCReSpawn>(this, startPos, spawnHeight, spawnDelay, gridStartPos);
	m_PossibleStates[EState::respawn]->OnStateSwitch.AddObserver(this);
	
	//---------------------------------------------------------------------------------
	//Wrongway
	if (m_Type == ECharacterType::wrong)

	{

		int frame = isType2 ? 4 : 0;
		spriteComp->UpdateFrame(frame);

		bool left = (rand() % 100) % 2 == 0;
		gridStartPos = left ? std::make_pair(6, 0) : std::make_pair(0, 6);


		const float DieTime{ 0.25f };
		m_PossibleStates[EState::dead] = std::make_unique<PurpleDead>(this, DieTime);
		m_PossibleStates[EState::dead]->OnStateSwitch.AddObserver(this);

		const float idleTime{ 1.f };
		m_PossibleStates[EState::idle] = std::make_unique<WrongIdle>(this, idleTime, left);
		m_PossibleStates[EState::idle]->OnStateSwitch.AddObserver(this);

		m_PossibleStates[EState::walking] = std::make_unique<WalkingWrongState>(this);
		m_PossibleStates[EState::walking]->OnStateSwitch.AddObserver(this);

		startPos = TG::Transform::CalculateGridPosition(gridStartPos.first, gridStartPos.second, jumpOffset, m_ZeroPosition);
		m_PossibleStates[EState::falling] = std::make_unique<Falling>(this, 0.2f);
		m_PossibleStates[EState::falling]->OnStateSwitch.AddObserver(this);
		m_PossibleStates[EState::respawn] = std::make_unique<WrongReSpawn>(this, startPos, spawnHeight, spawnDelay, gridStartPos);
		m_PossibleStates[EState::respawn]->OnStateSwitch.AddObserver(this);
	}

}

void Game::NPC::ApplyGameMode(int gameMode, int )
{
	TG::EGameMode mode = static_cast<TG::EGameMode>(gameMode);

	if (CheckComponent<Player2Component>())
	{
		if (mode != TG::EGameMode::vs )
		{
			SetPositionOnGridByIndex(12, 0, m_JumpOffset);
			m_CharacterState = m_PossibleStates[EState::dead].get();
			OnActivateInput.OnNotifyAll(false);

		}
		else
		{
			m_CharacterState = m_PossibleStates[EState::dead].get();
			OnActivateInput.OnNotifyAll(true);
		}
		if (CheckComponent<EggComponent>())
		{
			GetComponent<EggComponent>()->HatchEgg(false);
			if (CheckComponent<TG::SpriteComponent>())
				GetComponent<TG::SpriteComponent>()->UpdateFrame(1);
		}
	}
	else
		m_CharacterState = m_PossibleStates[EState::dead].get();

	//Make sure MoveComponent is not halfway movement
	if (CheckComponent<MovementComponent>())
		GetComponent<MovementComponent>()->ResetForNewMode();

}

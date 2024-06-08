#include "Cube.h"
#include "SpriteComponent.h"
#include <iostream>
#include "character.h"

Game::Cube::Cube(const glm::vec2& position, const ECubeProgressState& state, std::shared_ptr<TG::Texture2D> textureSPTR, std::pair<int, int>rowColum)
	:TG::GameObject()
	, m_State{state}
	, m_RowColumSprite{ rowColum }
{
	AddComponent<TG::RenderComponent>(this, textureSPTR);
	AddComponent<TG::SpriteComponent>(this, rowColum.second, rowColum.first, true);
	if (CheckComponent<TG::SpriteComponent>())
		GetComponent<TG::SpriteComponent>()->SetTimePerFrame(0.2f);
	SetLocalPosition(position);	
}

bool Game::Cube::UpdateProgressState(const ECharacterType& visiterType, int level)
{
	bool increaseScore{ ProgressOnLvl(visiterType, level) };

	if (CheckComponent<TG::SpriteComponent>() )
	{
		GetComponent<TG::SpriteComponent>()->UpdateFrame(static_cast<int>(m_State) * m_RowColumSprite.second + m_Round);
	}
	else
	{
		std::cout << "no valid spritecomponent available\n";
	}

	return increaseScore;
}

bool Game::Cube::IsFinalState(int lvl) const
{
	if (lvl == 2)
		return m_State == ECubeProgressState::endFase;

	return m_State == ECubeProgressState::intermediateFase;
}

bool Game::Cube::IsCollisionOnCube() const
{
	return m_vTypesOnCube.size() > 1;
}

void Game::Cube::AddVisiterOnCube(const ECharacterType& type)
{
	m_vTypesOnCube.push_back(type);
}

void Game::Cube::RemoveVisiterOnCube(const ECharacterType& type)
{
	m_vTypesOnCube.erase(std::remove(m_vTypesOnCube.begin(), m_vTypesOnCube.end(), type), m_vTypesOnCube.end());
}

Game::ECharacterType Game::Cube::GetDominantTypeOnCube() const
{
	if (std::find(m_vTypesOnCube.cbegin(), m_vTypesOnCube.cend(), ECharacterType::purple ) != m_vTypesOnCube.cend())
	{
		return ECharacterType::purple;
	}
	if (std::find(m_vTypesOnCube.cbegin(), m_vTypesOnCube.cend(), ECharacterType::wrong) != m_vTypesOnCube.cend())
	{
		return ECharacterType::purple;
	}
	if (std::find(m_vTypesOnCube.cbegin(), m_vTypesOnCube.cend(), ECharacterType::red) != m_vTypesOnCube.cend())
	{
		return ECharacterType::red;
	}
	return ECharacterType::green;
}

void Game::Cube::SetAnimationAuto()const
{
	if (CheckComponent<TG::SpriteComponent>())
		GetComponent<TG::SpriteComponent>()->SetAutomaiticMode(true);
}

void Game::Cube::ClearCube()
{
	m_vTypesOnCube.clear();
	m_State = ECubeProgressState::startFase;
}

void Game::Cube::SetLvlRound(int level, int round)
{
	m_Level = level;
	m_Round = round;
	if (CheckComponent<TG::SpriteComponent>())
	{
		GetComponent<TG::SpriteComponent>()->UpdateFrame(static_cast<int>(m_State) * m_RowColumSprite.second + m_Round);
	}
}

bool Game::Cube::ProgressOnLvl(const ECharacterType& visiterType, int level)
{
	bool increaseScore{ false };

	if (level == 1)
	{
		switch (visiterType)
		{
		case ECharacterType::green:
			if (m_State != ECubeProgressState::startFase)
			{
				m_State = static_cast<ECubeProgressState>(static_cast<int>(m_State) - 1);
			}
			break;
		case ECharacterType::red:
			if (m_State != ECubeProgressState::intermediateFase)
			{
				m_State = static_cast<ECubeProgressState>(static_cast<int>(m_State) + 1);
				increaseScore = true;
			}
			break;
		default:
			break;
		}
	}
	if (level == 2)
	{
		switch (visiterType)
		{
		case ECharacterType::green:
			if (m_State != ECubeProgressState::startFase)
			{
				m_State = static_cast<ECubeProgressState>(static_cast<int>(m_State) - 1);
			}
			break;
		case ECharacterType::red:
			if (m_State != ECubeProgressState::endFase)
			{
				m_State = static_cast<ECubeProgressState>(static_cast<int>(m_State) + 1);
				increaseScore = true;
			}
			break;
		default:
			break;
		}
	}
	if (level == 3)
	{
		switch (visiterType)
		{
		case ECharacterType::green:
			if (m_State != ECubeProgressState::startFase)
			{
				m_State = static_cast<ECubeProgressState>(static_cast<int>(m_State) - 1);
			}
			break;
		case ECharacterType::red:
			if (m_State == ECubeProgressState::startFase)
			{
				m_State = static_cast<ECubeProgressState>(static_cast<int>(m_State) + 1);
				increaseScore = true;
			}
			else if (m_State == ECubeProgressState::intermediateFase)
			{
				m_State = static_cast<ECubeProgressState>(static_cast<int>(m_State) - 1);
				increaseScore = false;
			}
			break;
		default:
			break;
		}
	}

	return increaseScore;
}

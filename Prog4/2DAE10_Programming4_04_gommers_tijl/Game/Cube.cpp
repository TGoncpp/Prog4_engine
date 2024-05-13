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

void Game::Cube::UpdateProgressState(const ECharacterType& visiterType)
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
		}
		break;
	default:
		break;
	}


	if (CheckComponent<TG::SpriteComponent>())
	{
		GetComponent<TG::SpriteComponent>()->UpdateFrame(static_cast<int>(m_State) * m_RowColumSprite.second);
	}
	else
	{
		std::cout << "no valid spritecomponent available\n";
	}
}

bool Game::Cube::IsFinalState() const
{
	return m_State == ECubeProgressState::endFase;
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
	if (std::find(m_vTypesOnCube.cbegin(), m_vTypesOnCube.cend(), ECharacterType::purple) != m_vTypesOnCube.cend())
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

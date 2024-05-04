#include "Cube.h"
#include "SpriteComponent.h"
#include <iostream>
#include "character.h"

Game::Cube::Cube(const glm::vec2& position, const ECubeProgressState& state, std::shared_ptr<TG::Texture2D> textureSPTR)
	:TG::GameObject()
	, m_State{state}
{
	AddComponent<TG::RenderComponent>(this, textureSPTR);
	AddComponent<TG::SpriteComponent>(this, 6, 3, true);
	if (CheckComponent<TG::SpriteComponent>())
		GetComponent<TG::SpriteComponent>()->SetTimePerFrame(0.2f);
	SetLocalPosition(position);	
}

void Game::Cube::UpdateProgressState()
{
	switch (m_State)
	{
	case ECubeProgressState::startFase:
		m_State = ECubeProgressState::intermediateFase;
		break;
	case ECubeProgressState::intermediateFase:
		m_State = ECubeProgressState::endFase;
		break;
	default:
		return;
	}

	if (CheckComponent<TG::SpriteComponent>())
	{
		GetComponent<TG::SpriteComponent>()->UpdateFrame(static_cast<int>(m_State));
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

Game::ECharacterType Game::Cube::GetDominantTypeOnCube() const
{
	if (std::find(m_vTypesOnCube.cbegin(), m_vTypesOnCube.cend(), ECharacterType::purple) != m_vTypesOnCube.cend())
	{
		return ECharacterType::purple;
	}
	return ECharacterType::red;
}

void Game::Cube::SetAnimationAuto()const
{
	if (CheckComponent<TG::SpriteComponent>())
		GetComponent<TG::SpriteComponent>()->SetAutomaiticMode(true);
}

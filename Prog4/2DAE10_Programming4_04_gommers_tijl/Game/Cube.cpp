#include "Cube.h"
#include "SpriteComponent.h"
#include <iostream>

Game::Cube::Cube(const glm::vec2& position, const CubeState& state, std::shared_ptr<TG::Texture2D> textureSPTR)
	:TG::GameObject()
	, m_State{state}
{
	AddComponent<TG::RenderComponent>(this, textureSPTR);
	AddComponent<TG::SpriteComponent>(this, 6, 3, true);
	if (CheckComponent<TG::SpriteComponent>())
		GetComponent<TG::SpriteComponent>()->SetTimePerFrame(0.2f);
	SetLocalPosition(position);	
}

void Game::Cube::UpdateState()
{
	switch (m_State)
	{
	case CubeState::startFase:
		m_State = CubeState::intermediateFase;
		break;
	case CubeState::intermediateFase:
		m_State = CubeState::endFase;
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
	return m_State == CubeState::endFase;
}

void Game::Cube::SetAnimationAuto()const
{
	if (CheckComponent<TG::SpriteComponent>())
		GetComponent<TG::SpriteComponent>()->SetAutomaiticMode(true);
}

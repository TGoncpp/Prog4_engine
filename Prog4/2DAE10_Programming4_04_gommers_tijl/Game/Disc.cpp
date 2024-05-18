#include "Disc.h"
#include "MovementComponent.h"
#include "SpriteComponent.h"
#include "Texture2D.h"
#include "Grid.h"
#include "Character.h"

Game::Disc::Disc(std::shared_ptr<TG::Texture2D> textureSPTR, const glm::vec2& gridTop, const glm::vec2& offset)
{
	const std::pair<int, int> spriteRowsColums{ textureSPTR->GetSpriteRowColum() };
	int texWidth{ textureSPTR->GetSize().x / (spriteRowsColums.second) };
	m_EndPos = glm::vec2{ gridTop.x - texWidth/2.f, gridTop.y + textureSPTR->GetSize().y / 2.f } - glm::vec2{ 0.f, m_HeightAbove };
	
	//Set random start position
	m_Depth   = rand() % 8;
	m_IsLeft = (rand() % 100) % 2 == 0;
	SetStartLocation(3, m_IsLeft, offset);

	//Add components
	AddComponent<Game::MovementComponent>(this);
	AddComponent<TG::RenderComponent>(this, textureSPTR);
	AddComponent<TG::SpriteComponent>(this, spriteRowsColums.second, spriteRowsColums.first, true);

	//Add components
	auto spriteComp = GetComponent<TG::SpriteComponent>();
	spriteComp->SetTimePerFrame (0.05f);
	auto MoveComp = GetComponent<MovementComponent>();
	MoveComp->SetMovementSpeed(40.f);
	MoveComp->OnReachedDestination.AddObserver(this);
	
}

void Game::Disc::Notify(std::pair<int, int> location, Character* character)
{
	m_Visiter = character;
	if (JumpedOnDisc(location))
	{
		character->SetParent(this, true);
		character->HandleInput(glm::vec2{0.f,0.f});
	}
	else
	{
		character->JumpOfGrid();
	}
}

void Game::Disc::Notify()
{
	m_Visiter->SetParent(nullptr, true);
	m_Visiter->HandleInput(glm::vec2{ 1.f,1.f });

}

void Game::Disc::OnSubjectDestroy()
{

}

void Game::Disc::SetGridSubject(Grid* subject)
{
	subject->OnDiscInteraction.AddObserver(this);
}

void Game::Disc::SetStartLocation(int depth, bool isLeft, const glm::vec2& offset)
{
	if (isLeft)
	{
		m_StartPos = TG::Transform::CalculateGridPosition(depth, 0, offset, m_EndPos);
	}
	else
	{
		m_StartPos = TG::Transform::CalculateGridPosition( 0, depth, offset, m_EndPos);
	}
	SetLocalPosition(m_StartPos);

}

bool Game::Disc::JumpedOnDisc(std::pair<int, int> newPosition)
{
	if (   ( m_IsLeft && newPosition.first == m_Depth + 1 && newPosition.second == -1)
		|| (!m_IsLeft && newPosition.second == m_Depth + 1 && newPosition.first == -1))
	{
		ActivateDisc();
		return true;
	}
	return false;
}

void Game::Disc::ActivateDisc()
{
	if (CheckComponent<MovementComponent>())
	{
		auto MoveComp = GetComponent<MovementComponent>();
		MoveComp->SetTargetLocation(m_EndPos);
	}
}

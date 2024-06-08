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
	m_Offset = offset;

	//Set random start position
	m_Depth = (rand() % 6) + 1;
	m_IsLeft = (rand() % 100) % 2 == 0;
	SetStartLocation(m_Depth, m_IsLeft);

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
	//character is set as nullptr to show that a round has just been finished
	if (character == nullptr)
	{
		//if disc is not been used, add points
		if (m_Depth != -1)
			OnDiscLeftScore.OnNotifyAll();
		ResetDisc();
		return;
	}

	if (JumpedOnDisc(location))
	{
		character->SetParent(this, true);
		character->HandleInput(glm::vec2{0.f,0.f});
		m_Visiter = character;
		m_Depth = -1;
	}
	//if this disc was not on the given location
	else if (m_Visiter == nullptr)
	{
		
		character->JumpOfGrid(true);
	}
}

void Game::Disc::Notify()
{
	m_Visiter->SetParent(nullptr, true);
	m_Visiter->GetCharacterState()->OnStateSwitch.OnNotifyAll(EState::respawn);
	m_Visiter = nullptr;

	if (CheckComponent<TG::RenderComponent>())
	{
		auto comp = GetComponent<TG::RenderComponent>();
		comp->SetVisibility(false);
	}
}

void Game::Disc::OnSubjectDestroy()
{

}

void Game::Disc::ApplyGameMode(int, int)
{
	ResetDisc();
}

void Game::Disc::SetGridSubject(Grid* subject)
{
	subject->OnDiscInteraction.AddObserver(this);
}

void Game::Disc::SetStartLocation(int depth, bool isLeft)
{
	if (isLeft)
	{
		m_StartPos = TG::Transform::CalculateGridPosition(depth, 0, m_Offset, m_EndPos);
	}
	else
	{
		m_StartPos = TG::Transform::CalculateGridPosition( 0, depth, m_Offset, m_EndPos);
	}
	SetLocalPosition(m_StartPos);

}

bool Game::Disc::JumpedOnDisc(std::pair<int, int> newPosition)
{
	if (   ( m_IsLeft && newPosition.first == m_Depth - 1 && newPosition.second == -1)
		|| (!m_IsLeft && newPosition.second == m_Depth - 1 && newPosition.first == -1))
	{
		ActivateDisc();
		return true;
	}
	return false;
}

void Game::Disc::ResetDisc()
{
	//Set random start position
	m_Depth = (rand() % 6) + 1;
	m_IsLeft = (rand() % 100) % 2 == 0;
	SetStartLocation(m_Depth, m_IsLeft);
	m_Visiter = nullptr;

	if (CheckComponent<TG::RenderComponent>())
	{
		auto comp = GetComponent<TG::RenderComponent>();
		comp->SetVisibility(true);
	}

}

void Game::Disc::ActivateDisc()const
{
	if (CheckComponent<MovementComponent>())
	{
		auto MoveComp = GetComponent<MovementComponent>();
		MoveComp->SetTargetLocation(m_EndPos);
	}
}

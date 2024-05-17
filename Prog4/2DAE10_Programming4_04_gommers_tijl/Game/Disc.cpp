#include "Disc.h"
#include "MovementComponent.h"
#include "SpriteComponent.h"
#include "Texture2D.h"

Game::Disc::Disc(std::shared_ptr<TG::Texture2D> textureSPTR, const glm::vec2& gridTop)
{
	const std::pair<int, int> spriteRowsColums{ textureSPTR->GetSpriteRowColum() };
	int texWidth{ textureSPTR->GetSize().x / (spriteRowsColums.second) };
	m_EndPos = glm::vec2{ gridTop.x - texWidth/2.f, gridTop.y + textureSPTR->GetSize().y / 2.f } - glm::vec2{ 0.f, m_HeightAbove };
	
	//Add components
	AddComponent<Game::MovementComponent>(this);
	AddComponent<TG::RenderComponent>(this, textureSPTR);
	AddComponent<TG::SpriteComponent>(this, spriteRowsColums.second, spriteRowsColums.first, true);

	auto spriteComp = GetComponent<TG::SpriteComponent>();
	spriteComp->SetTimePerFrame (0.05f);
	auto MoveComp = GetComponent<MovementComponent>();
	MoveComp->SetMovementSpeed(40.f);


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

	if (CheckComponent<MovementComponent>())
	{
		auto MoveComp = GetComponent<MovementComponent>();
		MoveComp->SetTargetLocation(m_EndPos);
	}
}

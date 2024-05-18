#include "MovementComponent.h"
#include "Transform.h"
#include "GameObject.h"

Game::MovementComponent::MovementComponent(TG::GameObject* ownerObjRefrence, const glm::vec2& cubeMeassures)
	:BaseComponent(ownerObjRefrence),
	m_JumpOffset{ cubeMeassures }
	
{
	m_NormalisedDirection = glm::normalize(cubeMeassures);
}

void Game::MovementComponent::SetTargetLocationIndex(const glm::vec2& direction)
{
	if (m_IsMoving)return;
	m_IsMoving = true;

	glm::vec2 currentPosition{ m_OwnerPTR->GetLocalPosition() };
	glm::vec2 offsetDirection{};
	offsetDirection.x = (TG::Transform::IsEqualVector(direction, glm::vec2{ 1.f, 0.f }) || TG::Transform::IsEqualVector(direction, glm::vec2{ 0.f,  1.f }))? 1.f : -1.f;
	offsetDirection.y = (TG::Transform::IsEqualVector(direction, glm::vec2{ 1.f, 0.f }) || TG::Transform::IsEqualVector(direction, glm::vec2{ 0.f, -1.f }))? 1.f : -1.f;

	TG::Transform::SetDirection(m_NormalisedDirection, offsetDirection);
	TG::Transform::SetDirection(m_JumpOffset, offsetDirection);
	m_TargetPosition = currentPosition + m_JumpOffset;

}

void Game::MovementComponent::SetTargetLocation(const glm::vec2& target)
{
	if (m_IsMoving)return;
	m_IsMoving =  true;

	glm::vec2 currentPosition{ m_OwnerPTR->GetLocalPosition() };

	m_JumpOffset = target - currentPosition;
	m_NormalisedDirection = glm::normalize(m_JumpOffset);
	m_TargetPosition = target;
}

void Game::MovementComponent::SetMoveOffset(const glm::vec2& offset)
{
	m_JumpOffset = offset;
}

void Game::MovementComponent::FixedUpdate(float dt)
{
	if (!m_IsMoving) return;

	glm::vec2 oldPosition{ m_OwnerPTR->GetLocalPosition() };
	glm::vec2 newPosition{ oldPosition + dt * m_MovementSpeed * m_NormalisedDirection };
	m_OwnerPTR->SetLocalPosition(newPosition);


	if (IsTargetReached(newPosition))
	{
		m_IsMoving      = false;
		m_OwnerPTR->SetLocalPosition(m_TargetPosition);
		OnReachedDestination.OnNotifyAll();
	}

}

bool Game::MovementComponent::StoppedMoving()const
{
	return !m_IsMoving;
}

bool Game::MovementComponent::IsTargetReached(const glm::vec2& newPosition)const
{
	return TG::Transform::IsEqualVector(newPosition, m_TargetPosition, 1.f) && m_OwnerPTR;
}

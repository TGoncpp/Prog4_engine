#include "MovementComponent.h"
#include "Transform.h"
#include "GameObject.h"

TG::MovementComponent::MovementComponent(TG::GameObject* ownerObjRefrence, const glm::vec2& startIndx, const glm::vec2& cubeMeassures, int gridSize)
	:BaseComponent(ownerObjRefrence),
	m_JumpOffset{ cubeMeassures },
	m_LocationIndex{ startIndx },
	m_GridSize{gridSize}
	
{
	m_NormalisedDirection = glm::normalize(cubeMeassures);
		
}

void TG::MovementComponent::SetTargetLocation(const glm::vec2& direction)
{
	if (m_IsMoving)return;
	m_IsMoving = true;

	glm::vec2 currentPosition{ m_OwnerPTR->GetLocalPosition() };
	glm::vec2 offsetDirection{};
	offsetDirection.x = (Transform::IsEqualVector(direction, glm::vec2{ 1.f, 0.f }) || Transform::IsEqualVector(direction, glm::vec2{ 0.f, 1.f }))? 1.f : -1.f;
	offsetDirection.y = (Transform::IsEqualVector(direction, glm::vec2{ 1.f, 0.f }) || Transform::IsEqualVector(direction, glm::vec2{  0.f, -1.f }))? 1.f : -1.f;

	Transform::SetDirection(m_NormalisedDirection, offsetDirection);
	Transform::SetDirection(m_JumpOffset, offsetDirection);
	m_TargetPosition = currentPosition + m_JumpOffset;
}

void TG::MovementComponent::FixedUpdate(float dt)
{
	if (!m_IsMoving) return;

	glm::vec2 oldPosition{ m_OwnerPTR->GetLocalPosition() };
	glm::vec2 newPosition{ oldPosition + dt * m_MovementSpeed * m_NormalisedDirection };
	m_OwnerPTR->SetLocalPosition(newPosition);

	if (Transform::IsEqualVector(newPosition, m_TargetPosition))
	{
		m_OwnerPTR->SetLocalPosition(m_TargetPosition);
		m_IsMoving      = false;

	}

}

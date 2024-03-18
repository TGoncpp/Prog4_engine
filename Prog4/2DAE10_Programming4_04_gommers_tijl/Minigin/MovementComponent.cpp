#include "MovementComponent.h"
#include "Transform.h"
#include "GameObject.h"


void TG::MovementComponent::UpdateMovement(glm::vec2 direction)
{
	m_Direction     = direction;
	m_IsMoving      = true;
}

void TG::MovementComponent::FixedUpdate(float dt)
{
	if (!m_IsMoving) return;
	glm::vec2 oldPosition{ m_OwnerPTR->GetLocalPosition() };
	glm::vec2 newPosition{ oldPosition + dt * m_MovementSpeed * m_Direction };
	m_OwnerPTR->SetLocalPosition(newPosition);

	m_IsMoving      = false;
	m_Direction     = {}; 
}

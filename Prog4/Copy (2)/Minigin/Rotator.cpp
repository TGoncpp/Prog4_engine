#include "Rotator.h"
#include "GameObject.h"


TG::RotatorComponent::RotatorComponent(dae::GameObject* ownerObj)
	:BaseComponent{ownerObj}
{
	
}

void TG::RotatorComponent::Update(float dt)
{
	if (!m_IsRotating || !m_OwnerPTR)
		return;
	

	m_CurrentAngle += m_RotationSpeed * dt;
	glm::vec3 newPos{};
	newPos.x =  m_RotationDistanceFromPoint * cosf(m_CurrentAngle);
	newPos.y =  m_RotationDistanceFromPoint * sinf(m_CurrentAngle);

	m_OwnerPTR->SetLocalPosition(newPos);

}

#include "SpriteComponent.h"
#include "gameObject.h"
#include <iostream>

TG::SpriteComponent::SpriteComponent(GameObject* owner, int colum, int row, bool autoUpdate)
	:BaseComponent(owner),
	m_RenderCompPTR{m_OwnerPTR->GetComponent<RenderComponent>()},
	m_Colum{colum},
	m_Row{row}, 
	m_AutoUpdate{autoUpdate}
{
	m_RenderCompPTR->SetSprite(m_Colum, m_Row);
}

void TG::SpriteComponent::Update(float elapsedTime)
{
	if (!m_AutoUpdate) return;

	m_RecorderdTime += elapsedTime;
	if (m_RecorderdTime >= m_AnimationSpeed )
	{
		++m_CurrentFrame %= m_Colum;
		std::cout << m_CurrentFrame << "\n";
		m_RecorderdTime -= m_AnimationSpeed;
		m_RenderCompPTR->UpdateCurrentFrame(m_CurrentFrame);
	}
}

void TG::SpriteComponent::SetAnimationSpeed(float speed)
{
	m_AnimationSpeed = speed;
}


#include "SpriteComponent.h"
#include "gameObject.h"
#include <iostream>

TG::SpriteComponent::SpriteComponent(GameObject* owner, int colum, int row, bool autoUpdate)
	:BaseComponent(owner),
	m_Colum{colum},
	m_Row{row}, 
	m_AutoUpdate{autoUpdate}
{
	if (m_OwnerPTR && m_OwnerPTR->CheckComponent< RenderComponent>())
	{
		m_RenderCompPTR = m_OwnerPTR->GetComponent<RenderComponent>();
		m_RenderCompPTR->SetSprite(m_Colum, m_Row);
	}
}

void TG::SpriteComponent::Update(float elapsedTime)
{
	if (!m_AutoUpdate) return;

	m_RecorderdTime += elapsedTime;
	if (m_RecorderdTime >= m_AnimationSpeed )
	{
		UpdateFrame();
		
	}
}

void TG::SpriteComponent::SetTimePerFrame(float speed)
{
	m_AnimationSpeed = speed;
}

void TG::SpriteComponent::UpdateFrame()
{
	++m_CurrentFrame %= m_Colum;
	m_RecorderdTime -= m_AnimationSpeed;
	m_RenderCompPTR->UpdateCurrentFrame(m_CurrentFrame);
}

void TG::SpriteComponent::UpdateFrame(int currentFrame)
{
	m_RenderCompPTR->UpdateCurrentFrame(currentFrame);
}


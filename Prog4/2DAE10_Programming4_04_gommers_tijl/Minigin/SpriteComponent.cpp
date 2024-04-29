#include "SpriteComponent.h"
#include "gameObject.h"

TG::SpriteComponent::SpriteComponent(GameObject* owner, int colum, int row)
	:BaseComponent(owner),
	m_RenderCompPTR{m_OwnerPTR->GetComponent<RenderComponent>()},
	m_Colum{colum},
	m_Row{row}
{
	m_RenderCompPTR->SetSprite(m_Colum, m_Row);
}

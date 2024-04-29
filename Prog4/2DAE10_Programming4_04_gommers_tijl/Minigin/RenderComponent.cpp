#include "RenderComponent.h"
#include "Texture2D.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"
#include <glm/glm.hpp>



TG::RenderComponent::RenderComponent(TG::GameObject* owner, const std::string& path)
	: BaseComponent(owner)
{
	SetTexture(path);
}

void TG::RenderComponent::Render() const
{
	if (!m_TextureSPTR || !m_OwnerPTR)return;

	glm::vec3 pos = m_OwnerPTR->GetWorldPosition();
	Renderer::GetInstance().RenderTexture(*m_TextureSPTR, pos.x, pos.y, m_Colum, m_Row);
}

void TG::RenderComponent::SetTexture(const std::string& filename)
{
	m_TextureSPTR = ResourceManager::GetInstance().LoadTexture(filename);
}

void TG::RenderComponent::SetSprite(int colum, int row)
{
	m_Row = row;
	m_Colum = colum;
}

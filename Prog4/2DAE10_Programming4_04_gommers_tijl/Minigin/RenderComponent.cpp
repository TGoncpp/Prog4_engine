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

TG::RenderComponent::RenderComponent(TG::GameObject* owner, std::shared_ptr<TG::Texture2D> texuteSPTR)
	: BaseComponent(owner)
{
	SetTexture(texuteSPTR);
}

void TG::RenderComponent::Render() const
{
	if (!m_TextureSPTR || !m_OwnerPTR)return;

	glm::vec3 pos = m_OwnerPTR->GetWorldPosition();
	Renderer::GetInstance().RenderTexture(*m_TextureSPTR, pos.x, pos.y, m_Colum, m_Row, m_CurrentFrame);
}

void TG::RenderComponent::SetTexture(const std::string& filename)
{
	m_TextureSPTR = ResourceManager::GetInstance().LoadTexture(filename);
}

void TG::RenderComponent::SetTexture(std::shared_ptr<TG::Texture2D> texuteSPTR)
{
	m_TextureSPTR = texuteSPTR;
}

void TG::RenderComponent::SetSprite(int colum, int row)
{
	m_Row = row;
	m_Colum = colum;
	m_CurrentFrame = 0;
}

void TG::RenderComponent::UpdateCurrentFrame( int frame)
{
	m_CurrentFrame = frame;
}

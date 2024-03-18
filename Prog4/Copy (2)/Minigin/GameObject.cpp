#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include <algorithm>

#include "RenderComponent.h"

void dae::GameObject::SetParent(GameObject* parent, bool keepWorldPosition)
{
	if (IsChild(parent) || parent == this || m_parentPtr == parent)
		return;
	if (parent == nullptr)
		SetLocalPosition(GetWorldPosition());
	else
	{
		if (keepWorldPosition)
			SetLocalPosition(GetWorldPosition() - parent->GetWorldPosition());
		SetPositionDirty();
	}

	if (m_parentPtr) 
		m_parentPtr->RemoveChild(this);

	m_parentPtr = parent;

	if (m_parentPtr) 
		m_parentPtr->AddChild(this);

}

bool dae::GameObject::IsChild(const GameObject* otherObj)const
{
	return std::ranges::any_of(m_vChildPtrs, [otherObj](GameObject* e) {return e == otherObj; });
}

void dae::GameObject::UpdateWorldPosition()
{
	if (m_IsPositionDirty)
	{
		if (m_parentPtr == nullptr)
			m_WorldTransform = m_LocalTransform;
		else
			SetWorldPosition(m_parentPtr->GetWorldPosition() + GetLocalPosition()) ;
	}
	m_IsPositionDirty = false;
}

void dae::GameObject::AddChild(GameObject* child)
{
	m_vChildPtrs.push_back(child);
}

void dae::GameObject::RemoveChild(GameObject* child)
{
	m_vChildPtrs.erase(std::remove_if(m_vChildPtrs.begin(), m_vChildPtrs.end(), [child](GameObject* e) {return child == e; }));
}

void dae::GameObject::Update(float dt)
{
	for (std::unique_ptr<TG::BaseComponent>const& comp : m_vComponentUPtrs)
	{
		comp->Update(dt);
	}
}

void dae::GameObject::Render() const
{

	for (std::unique_ptr<TG::BaseComponent>const& comp: m_vComponentUPtrs)
	{
		
		comp->Render();
	}
}

void dae::GameObject::SetLocalPosition(float x, float y)
{
	m_LocalTransform.SetPosition(x, y, 0.0f);
	SetPositionDirty();
}

void dae::GameObject::SetLocalPosition(const glm::vec3& pos)
{
	SetLocalPosition(pos.x, pos.y);
}

void dae::GameObject::SetWorldPosition(float x, float y)
{
	m_WorldTransform.SetPosition(x, y, 0.f);
}

void dae::GameObject::SetWorldPosition(const glm::vec3& pos)
{
	SetWorldPosition(pos.x, pos.y);
}

glm::vec3 dae::GameObject::GetWorldPosition()
{
	if (m_IsPositionDirty)
		UpdateWorldPosition();
	return m_WorldTransform.GetPosition();
}




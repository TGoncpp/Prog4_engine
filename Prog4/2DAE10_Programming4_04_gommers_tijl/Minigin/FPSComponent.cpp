#include "FPSComponent.h"
#include "TextComponent.h"
#include "GameObject.h"
#include <string>

TG::FPSComponent::FPSComponent(TG::GameObject* ownerObj)
	:BaseComponent(ownerObj)
{
}

void TG::FPSComponent::Update(float dt)
{
	m_fFps = 1 / dt;

	m_sFps = std::to_string(m_fFps) + "  FPS";

	if (m_RenderComp == nullptr)
		m_RenderComp = m_OwnerPTR->GetComponent< TextComponent>();

	m_RenderComp->SetText(m_sFps);
}

#include "TextComponent.h"
#include <stdexcept>
#include <SDL_ttf.h>
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "GameObject.h"

TG::TextComponent::TextComponent(GameObject* owner, const std::string& text, std::shared_ptr<Font> pFont, const glm::vec3& offset)
	:BaseComponent(owner),
	m_font{pFont},
	m_needsUpdate{true},
	m_text{text},
	m_textTexture{nullptr},
	m_Offset{offset}
{
}

void TG::TextComponent::Update(float dt)
{
	if (m_text == "")return;
	dt = 0.0f;
	if (m_needsUpdate)
	{
		const SDL_Color color = { 255,255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(TG::Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_textTexture = std::make_unique<Texture2D>(texture);
		m_needsUpdate = false;
	}
}

void TG::TextComponent::Render() const
{
	if (m_textTexture != nullptr || !m_OwnerPTR)
	{
		glm::vec3 pos = m_OwnerPTR->GetWorldPosition() + m_Offset;
		TG::Renderer::GetInstance().RenderTexture(*m_textTexture, pos.x, pos.y);
	}
}

void TG::TextComponent::SetText(const std::string& text)
{
	if (m_text == text)
		return;
	m_text        = text;
	m_needsUpdate = true;
}

void TG::TextComponent::SetOffset(const glm::vec2& offset)
{
	m_Offset = glm::vec3{ offset.x, offset.y, 0.f };
}

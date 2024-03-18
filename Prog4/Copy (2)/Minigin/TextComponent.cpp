#include "TextComponent.h"
#include <stdexcept>
#include <SDL_ttf.h>
#include "TextObject.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"

TG::TextComponent::TextComponent(dae::GameObject* owner, const std::string& text, std::shared_ptr<dae::Font> pFont)
	:BaseComponent(owner),
	m_font{pFont},
	m_needsUpdate{true},
	m_text{text},
	m_textTexture{nullptr}
{
}

void TG::TextComponent::Update(float dt)
{
	dt = 0.0f;
	if (m_needsUpdate)
	{
		const SDL_Color color = { 255,255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(dae::Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_textTexture = std::make_shared<dae::Texture2D>(texture);
		m_needsUpdate = false;
	}
}

void TG::TextComponent::Render() const
{
	if (m_textTexture != nullptr || !m_OwnerPTR)
	{
		glm::vec3 pos = m_OwnerPTR->GetWorldPosition();
		dae::Renderer::GetInstance().RenderTexture(*m_textTexture, pos.x, pos.y);
	}
}

void TG::TextComponent::SetText(const std::string& text)
{
	if (m_text == text)
		return;
	m_text        = text;
	m_needsUpdate = true;
}

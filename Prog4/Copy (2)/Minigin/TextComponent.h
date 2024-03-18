#pragma once

#include "BaseComponent.h"

namespace dae
{
	class Font;
	class Texture2D;
	class GameObject;
}

namespace TG
{
	class TextComponent final: public BaseComponent
	{
	public:
		TextComponent(dae::GameObject* owner, const std::string& text, std::shared_ptr<dae::Font> pFont);
		virtual ~TextComponent() override                 = default;
		TextComponent(const TextComponent&)               = delete;
		TextComponent(TextComponent&&)                    = delete;
		TextComponent& operator=(const TextComponent&)    = delete;
		TextComponent& operator=(TextComponent&&)         = delete;

		virtual void Update(float dt) override;
		virtual void Render() const override;

		void SetText(const std::string& text);

	private:
		bool m_needsUpdate;
		std::string m_text;
		std::shared_ptr<dae::Font> m_font;
		std::shared_ptr<dae::Texture2D> m_textTexture;
	};
}
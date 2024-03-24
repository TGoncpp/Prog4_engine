#pragma once

#include "BaseComponent.h"
#include "Texture2D.h"

namespace dae
{
	class Font;
	class GameObject;
}

namespace TG
{
	class TextComponent final: public BaseComponent
	{
	public:
		TextComponent(dae::GameObject* owner, const std::string& text, std::shared_ptr<dae::Font> pFont, const glm::vec3& offset = {});
		virtual ~TextComponent() override                 = default;
		TextComponent(const TextComponent&)               = delete;
		TextComponent(TextComponent&&)                    = delete;
		TextComponent& operator=(const TextComponent&)    = delete;
		TextComponent& operator=(TextComponent&&)         = delete;

		virtual void Update(float dt) override;
		virtual void FixedUpdate(float dt) override { (void)dt; };
		virtual void Render() const override;

		void SetText(const std::string& text);
		void SetOffset(const glm::vec2& offset);

	private:
		bool m_needsUpdate;
		glm::vec3 m_Offset{};
		std::string m_text;
		std::shared_ptr<dae::Font> m_font;
		std::unique_ptr<dae::Texture2D> m_textTexture;
	};
}
#pragma once

#include "BaseComponent.h"
#include "Texture2D.h"


namespace TG
{
	class Font;
	class GameObject;
	class TextComponent final: public BaseComponent
	{
	public:
		TextComponent(GameObject* owner, const std::string& text, std::shared_ptr<Font> pFont, const glm::vec3& offset = {});
		virtual ~TextComponent() override                 = default;
		TextComponent(const TextComponent&)               = delete;
		TextComponent(TextComponent&&)                    = delete;
		TextComponent& operator=(const TextComponent&)    = delete;
		TextComponent& operator=(TextComponent&&)         = delete;

		virtual void Update(float dt) override;
		virtual void FixedUpdate(float dt) override { (void)dt; };
		virtual void Render() const override;

		void SetVisibility(bool visibility);
		void SetText(const std::string& text);
		void SetOffset(const glm::vec2& offset);
		glm::vec2 GetTextSize()const;
		std::string GetText()const { return m_text; }

	private:
		bool m_IsVisible{ true };
		bool m_needsUpdate;
		glm::vec3 m_Offset{};
		std::string m_text;
		std::shared_ptr<Font> m_font;
		std::unique_ptr<Texture2D> m_textTexture;
	};
}
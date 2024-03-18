#pragma once

#include "BaseComponent.h"

namespace dae
{
	class Texture2D;
}

namespace TG
{
	class RenderComponent : public BaseComponent
	{
	public:
		virtual void Update(float dt) { dt = 0.f; };
		virtual void Render()const override;

		void SetTexture(const std::string& filename);
		std::shared_ptr<dae::Texture2D> GetTexture() { return m_TextureSPTR; };

		RenderComponent(dae::GameObject* owner, const std::string& path);
		virtual ~RenderComponent() = default;
		RenderComponent& operator=(const RenderComponent&) = delete;
		RenderComponent& operator=(RenderComponent&&)      = delete;
		RenderComponent(const RenderComponent&)            = delete;
		RenderComponent(RenderComponent&&)                 = delete;

	private:
		std::shared_ptr<dae::Texture2D> m_TextureSPTR{};
	};
}
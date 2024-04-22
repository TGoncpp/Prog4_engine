#pragma once

#include "BaseComponent.h"

namespace TG
{
	class Texture2D;
}

namespace TG
{
	class RenderComponent : public BaseComponent
	{
	public:
		virtual void Update(float dt) { dt = 0.f; };
		virtual void FixedUpdate(float dt) { dt = 0.f; };
		virtual void Render()const override;

		void SetTexture(const std::string& filename);
		std::shared_ptr<Texture2D> GetTexture() { return m_TextureSPTR; };

		RenderComponent(GameObject* owner, const std::string& path);
		virtual ~RenderComponent() = default;
		RenderComponent& operator=(const RenderComponent&) = delete;
		RenderComponent& operator=(RenderComponent&&)      = delete;
		RenderComponent(const RenderComponent&)            = delete;
		RenderComponent(RenderComponent&&)                 = delete;

	private:
		std::shared_ptr<Texture2D> m_TextureSPTR{};
	};
}
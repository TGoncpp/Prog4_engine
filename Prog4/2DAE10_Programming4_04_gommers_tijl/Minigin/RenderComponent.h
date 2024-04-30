#pragma once
#include "BaseComponent.h"

namespace TG
{
	class Texture2D;
	class RenderComponent : public BaseComponent
	{
	public:
		virtual void Update(float ) {  };
		virtual void FixedUpdate(float ) {  };
		virtual void Render()const override;

		void SetTexture(const std::string& filename);
		void SetTexture(std::shared_ptr<TG::Texture2D> texuteSPTR);
		std::shared_ptr<Texture2D> GetTexture() { return m_TextureSPTR; };

		RenderComponent(GameObject* owner, const std::string& path);
		RenderComponent(GameObject* owner, std::shared_ptr<TG::Texture2D> texuteSPTR);
		virtual ~RenderComponent() = default;
		RenderComponent& operator=(const RenderComponent&) = delete;
		RenderComponent& operator=(RenderComponent&&)      = delete;
		RenderComponent(const RenderComponent&)            = delete;
		RenderComponent(RenderComponent&&)                 = delete;

		void SetSprite(int colum, int row);
		void UpdateCurrentFrame(int frame);

	private:
		std::shared_ptr<Texture2D> m_TextureSPTR{};
		int m_Colum{ 1 };
		int m_Row{ 1 };
		int m_CurrentFrame{ -1 };
	};
}
#pragma once
#include "BaseComponent.h"
#include "RenderComponent.h"

namespace TG
{
	class SpriteComponent : public BaseComponent
	{
	public:
		virtual void Update(float)override {  };
		virtual void FixedUpdate(float)override {  };
		virtual void Render()const override {};


		SpriteComponent(GameObject* owner, int colum, int row);
		virtual ~SpriteComponent() = default;
		SpriteComponent& operator=(const SpriteComponent&) = delete;
		SpriteComponent& operator=(SpriteComponent&&) = delete;
		SpriteComponent(const SpriteComponent&) = delete;
		SpriteComponent(SpriteComponent&&) = delete;

		void SetSprite(int colum, int row);

	private:
		RenderComponent* m_RenderCompPTR{ nullptr };
		int m_Colum{ 1 };
		int m_Row{ 1 };
		int m_CurrentFrame{ -1 };
	};
}
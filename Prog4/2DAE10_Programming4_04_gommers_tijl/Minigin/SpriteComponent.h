#pragma once
#include "BaseComponent.h"
#include "RenderComponent.h"

namespace TG
{
	class SpriteComponent : public BaseComponent
	{
	public:
		virtual void Update(float elapsedTime)override;
		virtual void FixedUpdate(float)override {  };
		virtual void Render()const override {};


		SpriteComponent(GameObject* owner, int colum, int row, bool autoUpdate );
		virtual ~SpriteComponent() = default;
		SpriteComponent& operator=(const SpriteComponent&) = delete;
		SpriteComponent& operator=(SpriteComponent&&) = delete;
		SpriteComponent(const SpriteComponent&) = delete;
		SpriteComponent(SpriteComponent&&) = delete;

		void SetTimePerFrame(float speed);
		void UpdateFrame();
		void UpdateFrame(int currentFrame);
		void SetAutomaiticMode(bool isAutomatic);
		void SetTexture(RenderComponent* renderComp);

	private:
		RenderComponent* m_RenderCompPTR{ nullptr };
		const int m_Colum{ 1 };
		const int m_Row{ 1 };
		int m_CurrentFrame{ 0 };
		float m_AnimationSpeed{ 1.f };
		float m_RecorderdTime{ 0.f };
		bool m_AutoUpdate{ true };
	};
}
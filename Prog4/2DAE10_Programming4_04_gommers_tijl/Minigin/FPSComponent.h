#pragma once
#include "BaseComponent.h"

namespace dae
{
	class GameObject;
}

namespace TG
{
	class TextComponent;
	class FPSComponent final : public BaseComponent
	{
	public:
		FPSComponent(dae::GameObject* ownerObj);
		virtual ~FPSComponent() override = default;
		FPSComponent(const FPSComponent&) = delete;
		FPSComponent(FPSComponent&&) = delete;
		FPSComponent& operator=(const FPSComponent&) = delete;
		FPSComponent& operator=(FPSComponent&&) = delete;

		virtual void Update(float dt) override;
		virtual void FixedUpdate(float dt) override { (void)dt; };
		virtual void Render() const override {  };


	private:
		float m_fFps{ 0.0f };
		std::string m_sFps{ "" };
		TextComponent* m_RenderComp{ nullptr };
	};
}
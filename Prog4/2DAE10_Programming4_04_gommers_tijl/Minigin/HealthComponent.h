#pragma once
#include "BaseComponent.h"
#include "Subject.h"

namespace TG
{
	class HealthComponent : public BaseComponent
	{
	public:
		HealthComponent(dae::GameObject* owner, int startHealth);
		virtual ~HealthComponent()override = default;
		int GetHealth()const { return m_Health; };
		void DecreaseHealth(int decrement);
		Subject<> OnHealthChange;
		Subject<> OnDead;

		virtual void Update(float dt) { (void)dt; };
		virtual void FixedUpdate(float dt) { (void)dt; };
		virtual void Render()const {};


	private:
		int m_Health{3};
	};
}
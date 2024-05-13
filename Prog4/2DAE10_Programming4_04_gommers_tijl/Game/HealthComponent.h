#pragma once
#include "BaseComponent.h"
#include "Subject.h"

namespace Game
{
	class HealthComponent final : public TG::BaseComponent
	{
	public:
		HealthComponent(TG::GameObject* owner, int startHealth);
		virtual ~HealthComponent()override = default;
		HealthComponent& operator=(const HealthComponent&) = delete;
		HealthComponent& operator=(HealthComponent&&) = delete;
		HealthComponent(const HealthComponent&) = delete;
		HealthComponent(HealthComponent&&) = delete;


		int GetHealth()const { return m_Health; };
		void DecreaseHealth(int decrement);
		TG::Subject<> OnHealthChange;
		TG::Subject<const std::string&> OnDead;

		virtual void Update(float dt) { (void)dt; };
		virtual void FixedUpdate(float dt) { (void)dt; };
		virtual void Render()const {};


	private:
		int m_Health{3};
	};
}
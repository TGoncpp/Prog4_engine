#pragma once
#include "BaseComponent.h"
#include "Subject.h"
#include "character.h"

namespace Game
{
	class HealthComponent final : public TG::BaseComponent, public TG::IObserver<>
	{
	public:
		HealthComponent(TG::GameObject* owner, Character* Qbert, std::vector<TG::RenderComponent*> vHearths);
		virtual ~HealthComponent()override;
		HealthComponent& operator=(const HealthComponent&) = delete;
		HealthComponent& operator=(HealthComponent&&)      = delete;
		HealthComponent(const HealthComponent&)            = delete;
		HealthComponent(HealthComponent&&)                 = delete;

		void ResetHealth();
		int GetHealth()const { return m_Health; };
		TG::Subject<> OnGameOver;

		virtual void Update(float ) {};
		virtual void FixedUpdate(float ) {};
		virtual void Render()const {};

		virtual void Notify()override;
		virtual void OnSubjectDestroy()override {};


	private:
		std::vector<TG::RenderComponent*> m_vHearthRenderCompRef;
		Character* m_Subject;
		int m_Health{4};
		void DecreaseHealth(int decrement);
	};
}
#pragma once
#include "TextComponent.h"
#include "Observer.h"

namespace TG
{

	class HealthDisplay final : public IObserver<>, public BaseComponent 
	{
	public:
		HealthDisplay(dae::GameObject* owner, dae::GameObject* subjectOwner);
		virtual ~HealthDisplay() override              = default;
		HealthDisplay(const HealthDisplay&)            = delete;
		HealthDisplay(HealthDisplay&&)                 = delete;
		HealthDisplay& operator=(const HealthDisplay&) = delete;
		HealthDisplay& operator=(HealthDisplay&&)      = delete;

		virtual void Update(float dt) override { (void)dt; };
		virtual void FixedUpdate(float dt) override { (void)dt; };
		virtual void Render() const override {};

		virtual void Notify() override;
		virtual void OnSubjectDestroy() override;

	private:
		dae::GameObject* m_SubjectOwnrPtr;
		TextComponent* m_TextCompUPtr;
		void UpdateText();
	};

}
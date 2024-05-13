#pragma once
#include "TextComponent.h"
#include "Observer.h"

namespace Game
{

	class HealthDisplay final : public TG::IObserver<>, public TG::BaseComponent
	{
	public:
		HealthDisplay(TG::GameObject* owner, TG::GameObject* subjectOwner);
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
		TG::GameObject* m_SubjectOwnrPtr;
		TG::TextComponent* m_TextCompUPtr;
		void UpdateText();
	};

}
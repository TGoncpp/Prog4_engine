#pragma once
#include "BaseComponent.h"
#include <utility>

namespace Game
{
	class QbertCharacter;
	class ChaseCharacterComponent final : public TG::BaseComponent
	{
	public:
		ChaseCharacterComponent(TG::GameObject* owner, QbertCharacter* target)
			:BaseComponent(owner),
			m_TargetPtr{target} {}
		virtual ~ChaseCharacterComponent() override = default;
		ChaseCharacterComponent(const ChaseCharacterComponent&) = delete;
		ChaseCharacterComponent(ChaseCharacterComponent&&) = delete;
		ChaseCharacterComponent& operator=(const ChaseCharacterComponent&) = delete;
		ChaseCharacterComponent& operator=(ChaseCharacterComponent&&) = delete;

		virtual void Update(float) override {};
		virtual void FixedUpdate(float) override {  };
		virtual void Render() const override {};

		glm::vec2 GetDirectionToTarget()const;

	private:
		QbertCharacter* m_TargetPtr{ nullptr };


	};

}
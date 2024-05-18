#pragma once
#include "BaseComponent.h"
#include "subject.h"

class TG::Transform;

namespace Game
{

	class MovementComponent final : public TG::BaseComponent
	{
	public:
		MovementComponent(TG::GameObject* ownerObjRefrence, const glm::vec2& cubeMeassures = glm::vec2{0.f, 0.f});
		
		virtual~ MovementComponent() = default;

		void SetMovementSpeed(float newSpeed) { m_MovementSpeed = newSpeed; };

		float GetMovementSpeed()const { return m_MovementSpeed; };

		void SetTargetLocationIndex(const glm::vec2& offset);
		void SetTargetLocation(const glm::vec2& target);
		void SetMoveOffset(const glm::vec2& offset);

		virtual void Render()const  override{};
		virtual void Update(float )  override{  };
		virtual void FixedUpdate(float dt) override;

		bool StoppedMoving()const;
		TG::Subject<> OnReachedDestination;

	private:
		glm::vec2 m_JumpOffset{};
		glm::vec2 m_NormalisedDirection{};
		glm::vec2 m_TargetPosition{};
		float m_MovementSpeed{ 90.f };
		bool m_IsMoving{ false };

		bool IsTargetReached(const glm::vec2& newPosition)const;
	};

}

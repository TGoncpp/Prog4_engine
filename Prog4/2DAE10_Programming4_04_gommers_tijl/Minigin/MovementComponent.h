#pragma once
#include "BaseComponent.h"

class TG::Transform;

namespace TG
{

	class MovementComponent final : public BaseComponent
	{
	public:
		MovementComponent(TG::GameObject* ownerObjRefrence, const glm::vec2& startIndx, const glm::vec2& cubeMeassures, int gridSize);
		
		virtual~ MovementComponent() = default;

		void SetMovementSpeed(float newSpeed) { m_MovementSpeed = newSpeed; };

		float GetMovementSpeed()const { return m_MovementSpeed; };

		void SetTargetLocation(const glm::vec2& offset);

		virtual void Render()const  override{};
		virtual void Update(float )  override{  };
		virtual void FixedUpdate(float dt) override;

		bool StoppedMoving()const;

	private:
		glm::vec2 m_JumpOffset{};
		glm::vec2 m_NormalisedDirection{};
		glm::vec2 m_TargetPosition{};
		glm::vec2 m_LocationIndex{};
		float m_MovementSpeed{ 90.f };
		int m_GridSize{};
		bool m_IsMoving{ false };

		bool IsTargetReached(const glm::vec2& newPosition)const;
	};

}

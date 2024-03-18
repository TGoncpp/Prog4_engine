#pragma once
#include "BaseComponent.h"

class dae::Transform;

namespace TG
{

	class MovementComponent final : public BaseComponent
	{
	public:
		MovementComponent(dae::GameObject* ownerObjRefrence, float movementSpeed = 20.f)
			: BaseComponent(ownerObjRefrence),
			m_MovementSpeed{movementSpeed}
		{}
		
		virtual~ MovementComponent() = default;

		void SetMovementSpeed(float newSpeed) { m_MovementSpeed = newSpeed; };

		float GetMovementSpeed()const { return m_MovementSpeed; };

		void UpdateMovement(glm::vec2 direction);

		virtual void Render()const  override{};
		virtual void Update(float dt)  override{ (void)dt; };
		virtual void FixedUpdate(float dt) override;

	private:
		float m_MovementSpeed{ 20.f };
		glm::vec2 m_Direction{};
		bool m_IsMoving{ false };
	};

}

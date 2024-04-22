#pragma once
#include "BaseComponent.h"


namespace TG
{
	class GameObject;
	class RotatorComponent final : public BaseComponent
	{
	public:
		RotatorComponent(GameObject* ownerObj);
		virtual ~RotatorComponent() override = default;
		RotatorComponent(const RotatorComponent&) = delete;
		RotatorComponent(RotatorComponent&&) = delete;
		RotatorComponent& operator=(const RotatorComponent&) = delete;
		RotatorComponent& operator=(RotatorComponent&&) = delete;

		virtual void Update(float dt) override;
		virtual void FixedUpdate(float dt) override { (void)dt; };
		virtual void Render() const override { };

		void SetDistanceFromRotPoint(float newDistance) { m_RotationDistanceFromPoint = newDistance; };
		float GetDistanceToRotPoint()const { return m_RotationDistanceFromPoint; };
		float GetCurrentAngle()const { return m_CurrentAngle; };
		void SetRotatorState(bool isActive) { m_IsRotating = isActive; };
		bool GetRotatorState()const { return m_IsRotating ; };
		void SetRotationSpeed(float newSpeed) { m_RotationSpeed = newSpeed; };
		float SetRotationSpeed()const { return m_RotationSpeed ; };

	private:
		bool m_IsRotating{ true };
		float m_RotationSpeed{ 5.f };
		float m_CurrentAngle{ 0.0f };
		float m_RotationDistanceFromPoint{ 20.f };
		GameObject* m_OwnerObjSPTR{ nullptr };
	};
}
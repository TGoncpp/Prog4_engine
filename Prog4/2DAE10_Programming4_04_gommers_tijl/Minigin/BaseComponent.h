#pragma once
#include <memory>
#include <string>
#include "Transform.h"


namespace TG
{
	
	class GameObject;
	class BaseComponent
	{
	public:
		virtual void Update(float dt) = 0;
		virtual void FixedUpdate(float dt) = 0;
		virtual void Render()const = 0;

		BaseComponent(GameObject* owner) :m_OwnerPTR{ owner } {};
		virtual ~BaseComponent()                       = default;
		BaseComponent& operator=(const BaseComponent&) = delete;
		BaseComponent& operator=(BaseComponent&&)      = delete;
		BaseComponent(const BaseComponent&)            = delete;
		BaseComponent(BaseComponent&&)                 = delete;

	protected:
		GameObject* m_OwnerPTR;
	};
}
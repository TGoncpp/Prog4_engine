#pragma once
#include <memory>
#include <string>
#include "Transform.h"

namespace dae
{
	class GameObject;
}
namespace TG
{
	
	class BaseComponent
	{
	public:
		virtual void Update(float dt) = 0;
		virtual void Render()const = 0;

		BaseComponent(dae::GameObject* owner) :m_OwnerPTR{ owner } {};
		virtual ~BaseComponent()                       = default;
		BaseComponent& operator=(const BaseComponent&) = delete;
		BaseComponent& operator=(BaseComponent&&)      = delete;
		BaseComponent(const BaseComponent&)            = delete;
		BaseComponent(BaseComponent&&)                 = delete;

	protected:
		dae::GameObject* m_OwnerPTR;
	};
}
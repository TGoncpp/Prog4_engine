#pragma once
#include "BaseComponent.h"

namespace TG
{

	class MoveOnGridComponent final : public BaseComponent
	{
	public:
		MoveOnGridComponent(TG::GameObject* ownerObjRefrence);
		MoveOnGridComponent(const MoveOnGridComponent&)            = delete;
		MoveOnGridComponent(MoveOnGridComponent&&)                 = delete;
		MoveOnGridComponent& operator=(MoveOnGridComponent&&)      = delete;
		MoveOnGridComponent& operator=(const MoveOnGridComponent&) = delete;
		virtual~MoveOnGridComponent()                              = default;

		void UpdateMovement(glm::vec2 direction);

		virtual void Render()const  override {};
		virtual void Update(float )  override {};
		virtual void FixedUpdate(float) override {};

	private:
		glm::vec2 m_Direction{};
	};

}

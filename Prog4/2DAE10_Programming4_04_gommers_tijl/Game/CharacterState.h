#pragma once
#include "BaseComponent.h"

namespace Game
{
	enum class CharacterState
	{
		leftDown   = 3,
		leftUp     = 1,
		rightDown  = 2,
		rightUp    = 0
	};

	class CharacterStateComponent final : public TG::BaseComponent
	{
	public:
		CharacterStateComponent(TG::GameObject* ownerObjRefrence);
		~CharacterStateComponent()                                         = default;
		CharacterStateComponent(CharacterStateComponent&&)                 = delete;
		CharacterStateComponent(const CharacterStateComponent&)            = delete;
		CharacterStateComponent& operator=(const CharacterStateComponent&) = delete;
		CharacterStateComponent& operator=(CharacterStateComponent&&)      = delete;

		virtual void Render()const  override {};
		virtual void Update(float)  override { };
		virtual void FixedUpdate(float) override {};


		void UpdateProgressState(const glm::vec2& direction);

	private:
		CharacterState m_State{ CharacterState::leftDown };

	};
}

#pragma once
#include "BaseComponent.h"


namespace Game
{
	class EggComponent final :  public TG::BaseComponent
	{
	public:
		EggComponent(TG::GameObject* owner)
			:BaseComponent(owner){}
		virtual ~EggComponent() override = default;
		EggComponent(const EggComponent&) = delete;
		EggComponent(EggComponent&&) = delete;
		EggComponent& operator=(const EggComponent&) = delete;
		EggComponent& operator=(EggComponent&&) = delete;

		virtual void Update(float) override {  };
		virtual void FixedUpdate(float) override {  };
		virtual void Render() const override {};

		bool IsEgg()const { return m_IsEgg; }
		void HatchEgg(bool isHatched) { m_IsEgg = !isHatched; }

	private:
		bool m_IsEgg{ true };


	};

}
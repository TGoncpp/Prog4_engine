#pragma once

#include "BaseComponent.h"
#include "Subject.h"
#include "character.h"

namespace Game
{
	class LvlRoundComponent final : public TG::BaseComponent
	{
	public:
		LvlRoundComponent(TG::GameObject* owner);
		virtual ~LvlRoundComponent()override                   = default;
		LvlRoundComponent& operator=(const LvlRoundComponent&) = delete;
		LvlRoundComponent& operator=(LvlRoundComponent&&)      = delete;
		LvlRoundComponent(const LvlRoundComponent&)            = delete;
		LvlRoundComponent(LvlRoundComponent&&)                 = delete;


		virtual void Update(float)override;
		virtual void FixedUpdate(float)override {};
		virtual void Render()const override {};
		
		TG::Subject<int, int> OnNextPhase;
		TG::Subject<float> OnAnim;

		void NextRound();
		void NextLvl();
		void StartAnim();
		void Reset();

		int GetRound()const { return m_CurrentRound; }
		int GetLvl()const { return m_CurrentLvl; }
		int GetMaxLvl()const { return m_MaxLvls; }
		bool m_IsTransferring{ false };

	private:
		int m_CurrentLvl{ 1 };
		int m_CurrentRound{ 0 };
		const int m_MaxRound{ 5 };
		const int m_MaxLvls{ 3 };
		float m_CurrentTransferTime{};
		const float m_TransferTime{2.f};

	};
}

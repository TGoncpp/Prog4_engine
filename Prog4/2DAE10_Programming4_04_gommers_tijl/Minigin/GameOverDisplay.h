#pragma once
#include "TextComponent.h"
#include "Observer.h"
#include <vector>

namespace TG
{

	class GameOverDisplay final : public IObserver<const std::string& >, public BaseComponent
	{
	public:
		GameOverDisplay(dae::GameObject* owner, std::vector<dae::GameObject*> vSubjectOwner);
		virtual ~GameOverDisplay() override = default;
		GameOverDisplay(const GameOverDisplay&) = delete;
		GameOverDisplay(GameOverDisplay&&) = delete;
		GameOverDisplay& operator=(const GameOverDisplay&) = delete;
		GameOverDisplay& operator=(GameOverDisplay&&) = delete;

		virtual void Update(float dt) override { (void)dt; };
		virtual void FixedUpdate(float dt) override { (void)dt; };
		virtual void Render() const override {};

		virtual void Notify(const std::string& name) override;
		virtual void OnSubjectDestroy() override;

	private:
		TextComponent* m_TextCompUPtr;
		std::vector<dae::GameObject*> m_vSubjectOwnrPtrs;
		void UpdateText(const std::string& name);
		std::string m_Message{ "GAME OVER" };
		bool m_IsGameOver{ false };
	};

}
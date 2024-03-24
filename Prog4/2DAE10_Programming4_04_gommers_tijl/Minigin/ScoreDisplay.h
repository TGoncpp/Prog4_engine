#pragma once
#include "TextComponent.h"
#include "Observer.h"

namespace TG
{
	enum class LootType;

	class ScoreDisplay final : public IObserver<LootType>, public BaseComponent
	{
	public:
		ScoreDisplay(dae::GameObject* owner, dae::GameObject* subjectOwner);
		virtual ~ScoreDisplay() override               = default;
		ScoreDisplay(const ScoreDisplay&)              = delete;
		ScoreDisplay(ScoreDisplay&&)                   = delete;
		ScoreDisplay& operator=(const ScoreDisplay&)   = delete;
		ScoreDisplay& operator=(ScoreDisplay&&)        = delete;

		virtual void Update(float dt) override { (void)dt; };
		virtual void FixedUpdate(float dt) override { (void)dt; };
		virtual void Render() const override {};

		virtual void Notify(LootType loot) override;
		virtual void OnSubjectDestroy() override;

	private:
		dae::GameObject* m_SubjectOwnrPtr;
		TextComponent* m_TextCompUPtr;
		int m_Score{};
		void UpdateScore(const LootType& loot);
		std::string UpdateMessage();
	};

}
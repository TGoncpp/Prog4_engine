#pragma once
#include "TextComponent.h"
#include "Observer.h"
#include <vector>
#include <memory>


namespace Game
{
	enum class LootType;

	class ScoreDisplay final : public TG::IObserver<LootType>, public TG::BaseComponent
	{
	public:
		ScoreDisplay(TG::GameObject* owner, TG::GameObject* subjectOwner);
		virtual ~ScoreDisplay() override               = default;
		ScoreDisplay(const ScoreDisplay&)              = delete;
		ScoreDisplay(ScoreDisplay&&)                   = delete;
		ScoreDisplay& operator=(const ScoreDisplay&)   = delete;
		ScoreDisplay& operator=(ScoreDisplay&&)        = delete;

		virtual void Update(float ) override {  };
		virtual void FixedUpdate(float ) override {  };
		virtual void Render() const override {};

		virtual void Notify(LootType loot) override;
		virtual void OnSubjectDestroy() override;


	private:
		TG::GameObject* m_SubjectOwnrPtr;
		TG::TextComponent* m_TextCompUPtr;
		int m_Score{};
		void UpdateScore(const LootType& loot);
		std::string UpdateMessage();


	};

}
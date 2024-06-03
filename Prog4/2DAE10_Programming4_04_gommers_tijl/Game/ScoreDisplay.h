#pragma once
#include "TextComponent.h"
#include "Observer.h"
#include "character.h"
#include <vector>
#include <memory>


namespace Game
{
	class ScoreComponent final : public TG::IObserver<const ECharacterType& >, public TG::BaseComponent
	{
	public:
		ScoreComponent(TG::GameObject* owner, std::vector<Character*> observedCharacters, TG::TextComponent* scoreDisplay);
		virtual ~ScoreComponent() override;
		ScoreComponent(const ScoreComponent&)              = delete;
		ScoreComponent(ScoreComponent&&)                   = delete;
		ScoreComponent& operator=(const ScoreComponent&)   = delete;
		ScoreComponent& operator=(ScoreComponent&&)        = delete;

		virtual void Update(float ) override {  };
		virtual void FixedUpdate(float ) override {  };
		virtual void Render() const override {};

		virtual void Notify(const ECharacterType& characterType) override;
		virtual void OnSubjectDestroy() override;

		void ResetScore();

	private:
		std::vector<Character*> m_ObservedCharacters;
		TG::GameObject* m_SubjectOwnrPtr;
		TG::TextComponent* m_TextCompUPtr;
		int m_Score{};
		int m_RedPoint{ 25 };
		int m_GreenPoint{ 300 };
		int m_PurplePoint{ 500 };
		int m_DiscLeftPoint{ 50 };
		void UpdateScore(const ECharacterType& characterType);
		std::string UpdateMessage();


	};

}
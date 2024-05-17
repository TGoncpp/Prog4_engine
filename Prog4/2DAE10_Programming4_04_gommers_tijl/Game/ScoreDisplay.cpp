#include "ScoreDisplay.h"
#include "GameObject.h"
#include "LootComponent.h"
#include <sdl_mixer.h>

Game::ScoreDisplay::ScoreDisplay(TG::GameObject* owner, TG::GameObject* subjectOwner)
	:BaseComponent(owner),
	IObserver<LootType>(),
	m_SubjectOwnrPtr{subjectOwner}
{
	if (m_SubjectOwnrPtr->CheckComponent<LootComponent>())
		m_SubjectOwnrPtr->GetComponent<LootComponent>()->OnScoreChange.AddObserver(this);

	m_TextCompUPtr = m_OwnerPTR->GetComponent<TG::TextComponent>();
	if (m_TextCompUPtr)
		m_TextCompUPtr->SetText(UpdateMessage());
}

//ObserverFunction
void Game::ScoreDisplay::Notify(LootType loot)
{
	UpdateScore(loot);

	if (m_TextCompUPtr)
		m_TextCompUPtr->SetText(UpdateMessage());
}

//ObserverFunction
void Game::ScoreDisplay::OnSubjectDestroy()
{
	m_SubjectOwnrPtr = nullptr;
}

void Game::ScoreDisplay::UpdateScore(const LootType& loot)
{
	switch (loot)
	{
	case LootType::dirt:
		m_Score += 1;
		break;
	case LootType::silver:
		m_Score += 10;
		break;
	case LootType::gold:
		m_Score += 50;
		break;
	default:
		break;
	}
	if (m_Score >= 500)
	{
		
	}
}

std::string Game::ScoreDisplay::UpdateMessage()
{
	std::string newScoreMessage;
	newScoreMessage += m_SubjectOwnrPtr->GetName();
	newScoreMessage += " score : ";
	newScoreMessage += std::to_string(m_Score);

	return newScoreMessage;

}

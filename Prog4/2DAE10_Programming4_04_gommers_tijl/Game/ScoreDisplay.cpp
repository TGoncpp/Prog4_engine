#include "ScoreDisplay.h"
#include "GameObject.h"
#include "Npc.h"
#include "HighScoreComponent.h"

#include "sceneManager.h"

Game::ScoreComponent::ScoreComponent(TG::GameObject* Owner, std::vector<Character*> observedCharacters, TG::TextComponent* scoreDisplay )
	:BaseComponent(Owner),
	IObserver<const ECharacterType&>(),
	m_ObservedCharacters{ observedCharacters },
	m_SubjectOwnrPtr{Owner}
{
	//Get display refrence
	m_TextCompUPtr = scoreDisplay;
	if (m_TextCompUPtr)
		m_TextCompUPtr->SetText(UpdateMessage());

	//subscribe to subjects
	for (auto& subject : observedCharacters)
	{
		subject->OnScore.AddObserver(this);
	}
}

Game::ScoreComponent::~ScoreComponent()
{
	for (auto& subject : m_ObservedCharacters)
	{
		subject->OnScore.RemoveObserver(this);
	}
}

//ObserverFunction
void Game::ScoreComponent::Notify(const ECharacterType& characterType)
{
	UpdateScore(characterType);

	if (m_TextCompUPtr)
		m_TextCompUPtr->SetText(UpdateMessage());
}

//ObserverFunction
void Game::ScoreComponent::OnSubjectDestroy()
{
	m_SubjectOwnrPtr = nullptr;
}

void Game::ScoreComponent::ResetScore()
{
	m_Score = 0;
	if (m_TextCompUPtr)
		m_TextCompUPtr->SetText(UpdateMessage());
}

void Game::ScoreComponent::UpdateScore(const ECharacterType& characterType)
{
	if (m_Score == 0)
	{
		//reset flag for highscoreComponent only when score was reset
		auto ob = TG::SceneManager::GetInstance().GetSceneOffState(TG::EMenuState::winner)->GetGO(0);
		if (ob->CheckComponent<HighscoreComponent>())
			ob->GetComponent<HighscoreComponent>()->ResetScoreFlag();
	}

	switch (characterType)
	{
	case ECharacterType::green:
			m_Score += m_GreenPoint;
			break;
		case ECharacterType::red:
			m_Score += m_RedPoint;
			break;
		case ECharacterType::purple:
			m_Score += m_PurplePoint;
			break;
		default:
			break;
	}
	static_cast<TG::WinnerState*>(TG::SceneManager::GetInstance().GetMenuOffState(TG::EMenuState::winner))->SetScore(m_Score);
}

std::string Game::ScoreComponent::UpdateMessage()
{
	std::string newScoreMessage;
	newScoreMessage += "Score : ";
	newScoreMessage += std::to_string(m_Score);

	return newScoreMessage;

}

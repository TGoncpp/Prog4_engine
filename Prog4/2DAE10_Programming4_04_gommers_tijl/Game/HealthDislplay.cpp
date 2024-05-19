#include "HealthDisplay.h"
#include "GameObject.h"
#include "HealthComponent.h"

Game::HealthDisplay::HealthDisplay(TG::GameObject* owner, TG::GameObject* subjectOwner)
	:BaseComponent(owner),
	IObserver<>(),
	m_SubjectOwnrPtr{subjectOwner}
{
	
	m_TextCompUPtr =  m_OwnerPTR->GetComponent< TG::TextComponent>();
	UpdateText();
}

void Game::HealthDisplay::Notify()
{
	UpdateText();
}

void Game::HealthDisplay::OnSubjectDestroy()
{
	m_SubjectOwnrPtr = nullptr;
}

void Game::HealthDisplay::UpdateText()
{

	std::string newText{ "lives " };
	newText += m_SubjectOwnrPtr->GetName();
	newText += " : ";
	newText += std::to_string(m_SubjectOwnrPtr->GetComponent<HealthComponent>()->GetHealth());

	if (m_TextCompUPtr)
		m_TextCompUPtr->SetText(newText);
}

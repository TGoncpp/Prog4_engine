#include "HealthDisplay.h"
#include "GameObject.h"
#include "HealthComponent.h"

TG::HealthDisplay::HealthDisplay(dae::GameObject* owner, dae::GameObject* subjectOwner)
	:BaseComponent(owner),
	IObserver<>(),
	m_SubjectOwnrPtr{subjectOwner}
{
	m_SubjectOwnrPtr->GetComponent< TG::HealthComponent>()->OnHealthChange.AddObserver(this);
	m_TextCompUPtr =  m_OwnerPTR->GetComponent< TG::TextComponent>();
	UpdateText();
}

void TG::HealthDisplay::Notify()
{
	UpdateText();
}

void TG::HealthDisplay::OnSubjectDestroy()
{

}

void TG::HealthDisplay::UpdateText()
{
	std::string newText{ "lives " };
	newText += m_SubjectOwnrPtr->GetName();
	newText += " : ";
	newText += std::to_string(m_SubjectOwnrPtr->GetComponent<HealthComponent>()->GetHealth());

	m_TextCompUPtr->SetText(newText);
}

#include "GameOverDisplay.h"

#include "HealthDisplay.h"
#include "GameObject.h"
#include "HealthComponent.h"

TG::GameOverDisplay::GameOverDisplay(TG::GameObject* owner, std::vector<TG::GameObject*> vSubjectOwner)
	:BaseComponent(owner),
	IObserver<const std::string&>(),
	m_vSubjectOwnrPtrs{ vSubjectOwner }
{
	for (auto& subject : m_vSubjectOwnrPtrs)
	{
		if (subject->CheckComponent<HealthComponent>())
			subject->GetComponent<TG::HealthComponent>()->OnDead.AddObserver(this);
	}

	m_TextCompUPtr = m_OwnerPTR->GetComponent< TG::TextComponent>();
}

void TG::GameOverDisplay::Update(float dt)
{
	(void)dt; 
	if (m_IsASubjectDirty)
	{
		for (auto& subject : m_vSubjectOwnrPtrs)
		{
			if (!subject->CheckComponent<HealthComponent>())
				subject = nullptr;
		}
	}
	m_IsASubjectDirty = false;
}

void TG::GameOverDisplay::Notify(const std::string& name)
{
	if (m_IsGameOver)return;

	UpdateText(name);
	m_IsGameOver = true;
}

void TG::GameOverDisplay::OnSubjectDestroy()
{
	
}

void TG::GameOverDisplay::UpdateText(const std::string& name)
{
	m_Message += " ";
	m_Message += name;

	m_TextCompUPtr->SetText(m_Message);
}

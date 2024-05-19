#include "GameOverDisplay.h"
#include "HealthDisplay.h"
#include "GameObject.h"
#include "HealthComponent.h"

Game::GameOverDisplay::GameOverDisplay(TG::GameObject* owner, std::vector<TG::GameObject*> vSubjectOwner)
	:TG::BaseComponent(owner),
	TG::IObserver<const std::string&>(),
	m_vSubjectOwnrPtrs{ vSubjectOwner }
{
	

	m_TextCompUPtr = m_OwnerPTR->GetComponent< TG::TextComponent>();
}

void Game::GameOverDisplay::Update(float dt)
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

void Game::GameOverDisplay::Notify(const std::string& name)
{
	if (m_IsGameOver)return;

	UpdateText(name);
	m_IsGameOver = true;
}

void Game::GameOverDisplay::OnSubjectDestroy()
{
	
}

void Game::GameOverDisplay::UpdateText(const std::string& name)
{
	m_Message += " ";
	m_Message += name;

	m_TextCompUPtr->SetText(m_Message);
}

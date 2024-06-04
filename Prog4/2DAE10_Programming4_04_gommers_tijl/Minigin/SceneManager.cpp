#include "SceneManager.h"
#include "Scene.h"

TG::Scene& TG::SceneManager::CreateScene(const EMenuState& menuState)
{
	m_mScenes[menuState] = std::make_unique<Scene>("scene");
	return *m_mScenes[menuState];
}

void TG::SceneManager::Update(float dt)
{
	m_CurrentMenu->Update(dt);

}

void TG::SceneManager::FixedUpdate(float dt)
{
	m_CurrentMenu->FixedUpdate(dt);

}

void TG::SceneManager::Render()
{
	m_mScenes[m_CurrentMenu->GetMenuType()]->Render();

}

void TG::SceneManager::LateUpdate()
{
	if (!m_IsMenuDirty)
		return;

	m_PrevioustMenu = m_CurrentMenu;
	m_CurrentMenu->OnExit();
	m_CurrentMenu = m_FutureMenu;
	m_CurrentMenu->OnEnter();

	m_FutureMenu = nullptr;
	m_IsMenuDirty = false;
}

void TG::SceneManager::HandleInput(const glm::vec2& signal)
{
	m_CurrentMenu->InputHandeling(signal);
}

void TG::SceneManager::Notify(const EMenuState& newState, int lvl)
{
	if (!m_mPossibleMenus.contains(newState))
		return;

	if (lvl != -1 )
		m_Lvl = lvl;

	if (m_Lvl > m_MaxLvl)
	{
		m_FutureMenu = m_mPossibleMenus[EMenuState::winner].get();
		m_IsMenuDirty = true;
		return;
	}


	switch (m_CurrentMenu->GetMenuType())
	{
	case EMenuState::intro:
		if (newState != EMenuState::selection )
			return;
		break;
	case EMenuState::selection:
		if (newState != EMenuState::controls )
			return;
		break;
	case EMenuState::controls:
		if (newState != EMenuState::intermediate )
			return;
		break;
	case EMenuState::intermediate:
		if (newState != EMenuState::game )
			return;
		break;
	case EMenuState::game:
		if (newState != EMenuState::gameOver && newState != EMenuState::pause && newState != EMenuState::intermediate && newState != EMenuState::winner)
			return;
		break;
	case EMenuState::pause:
		if (newState != EMenuState::selection && newState != EMenuState::game)
			return;
		break;
	case EMenuState::gameOver:
		if (newState != EMenuState::intro )
			return;
		break;
	case EMenuState::winner:
		if (newState != EMenuState::intro )
			return;
		break;
	default:
		break;
	}
	
	m_FutureMenu = m_mPossibleMenus[newState].get();
	m_IsMenuDirty = true;

}

void TG::SceneManager::CreateMenu()
{
	m_mPossibleMenus.insert(std::make_pair(EMenuState::intro, std::make_unique<IntroState>(this, m_mScenes[EMenuState::intro].get())));
	m_mPossibleMenus[EMenuState::intro]->OnStateSwitch.AddObserver(this);
	m_mPossibleMenus.insert(std::make_pair(EMenuState::selection, std::make_unique<SelectionState>(this, m_mScenes[EMenuState::selection].get())));
	m_mPossibleMenus[EMenuState::selection]->OnStateSwitch.AddObserver(this);
	m_mPossibleMenus.insert(std::make_pair(EMenuState::controls, std::make_unique<ControlsState>(this, m_mScenes[EMenuState::controls].get())));
	m_mPossibleMenus[EMenuState::controls]->OnStateSwitch.AddObserver(this);
	m_mPossibleMenus.insert(std::make_pair(EMenuState::intermediate, std::make_unique<IntermediateState>(this, m_mScenes[EMenuState::intermediate].get())));
	m_mPossibleMenus[EMenuState::intermediate]->OnStateSwitch.AddObserver(this);
	m_mPossibleMenus.insert(std::make_pair(EMenuState::game, std::make_unique<GameState>(this, m_mScenes[EMenuState::game].get())));
	m_mPossibleMenus[EMenuState::game]->OnStateSwitch.AddObserver(this);
	m_mPossibleMenus.insert(std::make_pair(EMenuState::gameOver, std::make_unique<GameOverState>(this, m_mScenes[EMenuState::gameOver].get())));
	m_mPossibleMenus[EMenuState::gameOver]->OnStateSwitch.AddObserver(this);
	m_mPossibleMenus.insert(std::make_pair(EMenuState::pause, std::make_unique<PauseState>(this, m_mScenes[EMenuState::pause].get())));
	m_mPossibleMenus[EMenuState::pause]->OnStateSwitch.AddObserver(this);
	m_mPossibleMenus.insert(std::make_pair(EMenuState::winner, std::make_unique<WinnerState>(this, m_mScenes[EMenuState::winner].get())));
	m_mPossibleMenus[EMenuState::winner]->OnStateSwitch.AddObserver(this);

	m_CurrentMenu = m_mPossibleMenus[EMenuState::intro].get();
}


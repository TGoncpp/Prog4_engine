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

	//for(auto& scene : m_mScenes)
	//{
	//	scene.second->Update(dt);
	//}
}

void TG::SceneManager::FixedUpdate(float dt)
{
	m_CurrentMenu->FixedUpdate(dt);

	//for(auto& scene : m_mScenes)
	//{
	//	scene.second->FixedUpdate(dt);
	//}
}

void TG::SceneManager::Render()
{
	m_mScenes[m_CurrentMenu->GetMenuType()]->Render();

	//for (const auto& scene : m_mScenes)
	//{
	//	scene.second->Render();
	//}
}

void TG::SceneManager::LateUpdate()
{
	if (!m_IsMenuDirty)
		return;
	m_CurrentMenu = m_FutureMenu;
	m_FutureMenu = nullptr;
	m_IsMenuDirty = false;
}

void TG::SceneManager::Notify(const EMenuState& newState)
{
	if (!m_mPossibleMenus.contains(newState))
		return;

	switch (m_CurrentMenu->GetMenuType())
	{
	case EMenuState::intro:
		if (newState != EMenuState::selection)
			return;
		break;
	case EMenuState::selection:
		if (newState != EMenuState::controls && newState != EMenuState::intermediate)
			return;
		break;
	case EMenuState::controls:
		if (newState != EMenuState::selection )
			return;
		break;
	case EMenuState::intermediate:
		if (newState != EMenuState::game )
			return;
		break;
	case EMenuState::game:
		if (newState != EMenuState::selection && newState != EMenuState::gameOver)
			return;
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

	m_CurrentMenu = m_mPossibleMenus[EMenuState::game].get();
}

TG::SceneManager::SceneManager()
{
	
}

//TG::Scene& TG::SceneManager::CreateScene(const std::string& name)
//{
//	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
//	//const auto& scene = std::make_unique<Scene>(name);
//	m_scenes.push_back(scene);
//	return *scene;
//}

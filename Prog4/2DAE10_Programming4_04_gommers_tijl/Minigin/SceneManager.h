#pragma once
#include <vector>
#include <map>
#include <string>
#include <memory>
#include "Singleton.h"
#include "MenuState.h"
#include "Scene.h"

namespace TG
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>, public IObserver<const EMenuState&, int>
	{
		friend Scene::Scene(const std::string& name);
	public:
		Scene& CreateScene(const EMenuState& menuState);

		void Update(float);
		void FixedUpdate(float);
		void Render();
		void LateUpdate();

		//signal ENTER -> 0,0
		//signal Quit  -> 1,0
		void HandleInput(const glm::vec2& direction);

		MenuState* GetMenustate()const { return m_CurrentMenu; }
		Scene* GetSceneOffState(const EMenuState& state) { return m_mScenes[state].get(); }
		MenuState* GetMenuOffState(const EMenuState& state) { return m_mPossibleMenus[state].get(); }
		EMenuState GetPreviousMenuState()const { return m_PrevioustMenu->GetMenuType(); }
		int GetCurrentLvl()const { return m_Lvl; }

		void CreateMenu();
		
		void UpdateGameMode(const EGameMode& newGameMode) { m_ActiveGameMode = newGameMode; }
		int GetActiveGameModeIndex()const { return static_cast<int>(m_ActiveGameMode); }
	private:
		friend class Singleton<SceneManager>;
		SceneManager();
		
		virtual void Notify(const EMenuState& newState, int lvl = -1)override;
		virtual void OnSubjectDestroy()override {};

		std::map< EMenuState, std::unique_ptr<Scene>> m_mScenes;
		std::map< EMenuState, std::unique_ptr<MenuState>> m_mPossibleMenus;
		MenuState* m_PrevioustMenu{nullptr};
		MenuState* m_CurrentMenu{nullptr};
		MenuState* m_FutureMenu{nullptr};
		EGameMode m_ActiveGameMode{ EGameMode::single };
		int m_Lvl{ 1 };
		bool m_IsMenuDirty{false};
	};
}

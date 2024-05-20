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
	class SceneManager final : public Singleton<SceneManager>, public IObserver<const EMenuState&>
	{
		friend Scene::Scene(const std::string& name);
	public:
		Scene& CreateScene(const EMenuState& menuState);

		void Update(float);
		void FixedUpdate(float);
		void Render();
		void LateUpdate();

		virtual void Notify(const EMenuState& newState)override;
		virtual void OnSubjectDestroy()override {};

		MenuState* GetMenustate()const { return m_CurrentMenu; }
		void CreateMenu();
	private:
		friend class Singleton<SceneManager>;
		SceneManager();
		
		std::map< EMenuState, std::unique_ptr<Scene>> m_mScenes;
		std::map< EMenuState, std::unique_ptr<MenuState>> m_mPossibleMenus;
		MenuState* m_CurrentMenu{nullptr};
		MenuState* m_FutureMenu{nullptr};
		bool m_IsMenuDirty{false};
	};
}

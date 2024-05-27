#pragma once
#include <glm/glm.hpp>
#include"Subject.h"
//#include"Scene.h"

namespace TG
{
	class Scene;
	class SceneManager;
	//-----------------------------------------
	//INTERFACE
	//---------------------------------------
	enum class EMenuState
	{
		intro,
		selection,
		controls,
		intermediate,
		game,
		pause,
		gameOver
	};

	class IMenuState
	{
	public:
		IMenuState(){}

		void virtual InputHandeling(const glm::vec2&) = 0;
		void virtual OnEnter() = 0;
		void virtual Update(float) = 0;
		void virtual FixedUpdate(float) = 0;
		void virtual OnExit() = 0;

	};

	//-----------------------------------------
	//STATES
	//-----------------------------------------
	class MenuState : public IMenuState
	{
	public:
		MenuState(SceneManager* sceneManager, Scene* scene)
			:IMenuState(),
			m_OwnerObject{ sceneManager },
			m_ActiveScene{scene}{}

		void virtual InputHandeling(const glm::vec2&) {};
		void virtual OnEnter() {};
		void virtual Update(float) {};
		void virtual FixedUpdate(float){} ;
		void virtual OnExit(){} ;

		Subject<const EMenuState&> OnStateSwitch{};
		EMenuState GetMenuType()const { return m_MenuType; }

	protected:
		SceneManager* m_OwnerObject{};
		Scene* m_ActiveScene{};
		EMenuState m_MenuType{ EMenuState::game };
	};

	class IntroState final : public MenuState
	{
	public:
		IntroState(SceneManager* sceneManager, Scene* owner)
			:MenuState(sceneManager, owner )
		{
			m_MenuType = EMenuState::intro;
		}

		void virtual InputHandeling(const glm::vec2&);
		void virtual OnExit(){} ;

	};
	
	class ControlsState final : public MenuState
	{
	public:
		ControlsState(SceneManager* sceneManager, Scene* owner)
			:MenuState(sceneManager, owner ) 
		{
			m_MenuType = EMenuState::controls;
		}

		void virtual InputHandeling(const glm::vec2&);
		
	};
	
	class SelectionState final : public MenuState
	{
		enum class EGameMode
		{
			single,
			coop,
			vs
		};
	public:
		SelectionState(SceneManager* sceneManager, Scene* owner)
			:MenuState(sceneManager, owner ) 
		{
			m_MenuType = EMenuState::selection;
		}
		void virtual InputHandeling(const glm::vec2&);

	private:
		EGameMode m_GameMode{ EGameMode::single };
	};
	
	class IntermediateState final : public MenuState
	{
	public:
		IntermediateState(SceneManager* sceneManager, Scene* owner)
			:MenuState(sceneManager, owner ) 
		{
			m_MenuType = EMenuState::intermediate;
		}
		void virtual InputHandeling(const glm::vec2&) ;
		

	};
	
	class GameState final : public MenuState
	{
	public:
		GameState(SceneManager* sceneManager, Scene* owner)
			:MenuState(sceneManager, owner ) 
		{
			m_MenuType = EMenuState::game;
		}

		void virtual InputHandeling(const glm::vec2&) ;
		void virtual OnEnter() ;
		void virtual Update(float) ;
		void virtual FixedUpdate(float) ;
		void virtual OnExit() ;

	};
	
	class PauseState final : public MenuState
	{
	public:
		PauseState(SceneManager* sceneManager, Scene* owner, Scene* gameScene)
			:MenuState(sceneManager, owner ),
			m_GameScenePtr{gameScene}
		{
			m_MenuType = EMenuState::pause;
		}

		//signal stands for ENTER: 0,random
		//signal stands for QUIT   1,random
		void virtual InputHandeling(const glm::vec2&) ;
		
		void virtual OnExit(){} ;
	private:
		Scene* m_GameScenePtr{ nullptr };

	};
	
	class GameOverState final : public MenuState
	{
	public:
		GameOverState(SceneManager* sceneManager, Scene* owner)
			:MenuState(sceneManager, owner ) 
		{
			m_MenuType = EMenuState::game;
		}

		void virtual InputHandeling(const glm::vec2&) {};
		void virtual OnEnter(const glm::vec2&) {};
		void virtual Update(float) {};
		void virtual FixedUpdate(float){} ;
		void virtual OnExit(){} ;

	};

}
#pragma once
#include <glm/glm.hpp>
#include"Subject.h"
//#include"Scene.h"

namespace TG
{
	class Scene;
	class SceneManager;
	//-----------------------------------------
	//ENUMERATIONS
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
	enum class EGameMode
	{
		single = 0,
		vs     = 1,
		coop   = 2
	};
	//-----------------------------------------
	//INTERFACE
	//---------------------------------------
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
		void UpdateGameMode(float Ydirection);
		EGameMode m_GameMode{ EGameMode::single };

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
		void virtual OnEnter();
		
	};
	
	class SelectionState final : public MenuState
	{
		
	public:
		SelectionState(SceneManager* sceneManager, Scene* owner)
			:MenuState(sceneManager, owner ) 
		{
			m_MenuType = EMenuState::selection;
		}
		void virtual InputHandeling(const glm::vec2&);
		void virtual OnExit();

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
		void virtual OnEnter() ;
		
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
		PauseState(SceneManager* sceneManager, Scene* owner)
			:MenuState(sceneManager, owner )
		{
			m_MenuType = EMenuState::pause;
		}

		//signal stands for ENTER: 0,0
		//signal stands for QUIT   1,0
		void virtual InputHandeling(const glm::vec2&) ;

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
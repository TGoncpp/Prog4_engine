#pragma once
#include "GameObject.h"
#include "BaseComponent.h"
#include "Scene.h"


namespace Game
{

	enum class CubeState
	{
		empty,
		endFase,
		intermediateFase,
		startFase
	};
	
	class Cube final : public TG::GameObject
	{
	public:
		Cube(const glm::vec2& position, const CubeState& state, const std::string& name);
		~Cube()                                   = default;
		Cube& operator=(const Cube&)              = delete;
		Cube& operator=(Cube&&)                   = delete;
		Cube(const Cube&)                         = delete;
		Cube(Cube&&)                              = delete;
	
	private:
		CubeState m_State{CubeState::empty};

	};
}
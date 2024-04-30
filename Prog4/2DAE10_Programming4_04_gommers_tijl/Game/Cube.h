#pragma once
#include "GameObject.h"
#include "BaseComponent.h"
#include "Scene.h"


namespace Game
{

	enum class CubeState
	{
		empty = -1,
		startFase = 1,
		intermediateFase = 2,
		endFase = 3
	};
	
	class Cube final : public TG::GameObject
	{
	public:
		Cube(const glm::vec2& position, const CubeState& state, std::shared_ptr<TG::Texture2D> texuteSPTR);
		Cube()                                    = default;
		~Cube()                                   = default;
		Cube& operator=(const Cube&)              = delete;
		Cube& operator=(Cube&&)                   = delete;
		Cube(const Cube&)                         = delete;
		Cube(Cube&&)                              = delete;
	
		void UpdateState();

	private:
		CubeState m_State{CubeState::empty};

	};
}
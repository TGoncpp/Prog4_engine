#pragma once
#include "GameObject.h"
#include "BaseComponent.h"
#include "Scene.h"
#include <vector>


namespace Game
{
	enum class ECharacterType;

	enum class ECubeProgressState
	{
		empty = -1,
		startFase = 1,
		intermediateFase = 2,
		endFase = 3
	};

	
	class Cube final : public TG::GameObject
	{
	public:
		Cube(const glm::vec2& position, const ECubeProgressState& state, std::shared_ptr<TG::Texture2D> texuteSPTR);
		Cube()                                    = default;
		~Cube()                                   = default;
		Cube& operator=(const Cube&)              = delete;
		Cube& operator=(Cube&&)                   = delete;
		Cube(const Cube&)                         = delete;
		Cube(Cube&&)                              = delete;
	
		void UpdateProgressState();
		bool IsFinalState()const;
		bool IsCollisionOnCube()const;
		void AddVisiterOnCube(const ECharacterType& type);
		void RemoveVisiterOnCube(const ECharacterType& type);
		ECharacterType GetDominantTypeOnCube()const;
		void SetAnimationAuto()const;

	private:
		ECubeProgressState m_State{ECubeProgressState::empty};
		std::vector<ECharacterType> m_vTypesOnCube;
	};
}
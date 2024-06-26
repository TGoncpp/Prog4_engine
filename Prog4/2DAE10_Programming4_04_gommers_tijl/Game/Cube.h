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
		empty             = -1,
		startFase         = 0,
		intermediateFase  = 1,
		endFase           = 2
	};

	
	class Cube final : public TG::GameObject
	{
	public:
		Cube(const glm::vec2& position, const ECubeProgressState& state, std::shared_ptr<TG::Texture2D> texuteSPTR, std::pair<int, int>rowColum);
		Cube()                                    = default;
		~Cube()                                   = default;
		Cube& operator=(const Cube&)              = delete;
		Cube& operator=(Cube&&)                   = delete;
		Cube(const Cube&)                         = delete;
		Cube(Cube&&)                              = delete;
	
		bool UpdateProgressState(const ECharacterType& visiterType, int level);
		bool IsFinalState(int lvl)const;
		bool IsCollisionOnCube()const;
		void AddVisiterOnCube(const ECharacterType& type);
		void RemoveVisiterOnCube(const ECharacterType& type);
		ECharacterType GetDominantTypeOnCube()const;
		void SetAnimationAuto()const;

		void ClearCube();
		void SetLvlRound(int level, int round);

	private:
		ECubeProgressState m_State{ECubeProgressState::empty};
		std::vector<ECharacterType> m_vTypesOnCube;
		std::pair<int, int>m_RowColumSprite;
		int m_Round{ 0 };
		int m_Level{ 0 };

		bool ProgressOnLvl(const ECharacterType& visiterType, int level);
	};
}
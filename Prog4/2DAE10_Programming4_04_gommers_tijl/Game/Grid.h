#pragma once
#include "Cube.h"
#include "Observer.h"
#include "character.h"

namespace Game
{
	class Grid final : public TG::GameObject, public TG::IObserver<Character*, bool>, public TG::IObserver<> 
	{
	public:
		Grid(const glm::vec2& position, int size, std::shared_ptr<TG::Texture2D> textureSPTR);
		~Grid();
		Grid(Grid&&)                  = delete;
		Grid(const Grid&)             = delete;
		Grid& operator= (const Grid&) = delete;
		Grid& operator= (Grid&&)      = delete;

		//Components
		virtual void Render()const override;
		virtual void Update(float time) override;

		//IObserver
		virtual void Notify(Character* object, bool isMoving)override;
		virtual void Notify()override;
		virtual void OnSubjectDestroy();

		glm::vec2 GetCubeSize()const;
		void SetGridSubject(Game::Character* subjectToObserve);

		TG::Subject < std::pair<int, int>,Character* > OnDiscInteraction;

	private:
		std::vector<std::vector<std::unique_ptr<Cube>>> m_vGrid;
		glm::vec2 m_CubeSize{};
		std::vector<Game::Character*> m_vSubjectOwnrPtr;
		bool m_IsLevelFinished{ false };

		bool CheckLevelState();

	};
}
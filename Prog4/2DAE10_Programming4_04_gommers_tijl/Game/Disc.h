#pragma once
#include "GameObject.h"
#include "subject.h"

namespace Game
{
	class Grid;
	class Character;
	class Disc : public TG::GameObject, public TG::IObserver< std::pair<int, int>, Character*>, public TG::IObserver<>
	{
	public:
		Disc(std::shared_ptr<TG::Texture2D> textureSPTR, const glm::vec2& gridTop, const glm::vec2& offset);
		~Disc()                      = default;
		Disc(Disc&&)                 = delete;
		Disc(const Disc&)            = delete;
		Disc& operator=(Disc&&)      = delete;
		Disc& operator=(const Disc&) = delete;

		//Observer overloads
		virtual void Notify(std::pair<int, int>, Character*)override;
		virtual void Notify()override;
		virtual void OnSubjectDestroy();
		virtual void ApplyGameMode(int, int) override;

		void SetGridSubject(Grid* subject);

	private:
		Character* m_Visiter;
		glm::vec2 m_StartPos;
		glm::vec2 m_EndPos;
		glm::vec2 m_Direction;
		glm::vec2 m_Offset;
		float m_HeightAbove{ 55.f };
		int m_Depth{};
		bool m_IsLeft{ false };

		void SetStartLocation(int depth, bool isLeft);
		void ActivateDisc()const;
		bool JumpedOnDisc(std::pair<int, int> newPosition);
		void ResetDisc();
	};
}
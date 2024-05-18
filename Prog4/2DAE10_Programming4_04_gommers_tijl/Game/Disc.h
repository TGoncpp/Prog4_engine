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

		void SetGridSubject(Grid* subject);

	private:
		Character* m_Visiter;
		glm::vec2 m_StartPos;
		glm::vec2 m_EndPos;
		glm::vec2 m_Direction;
		float m_HeightAbove{ 55.f };
		int m_Depth{};
		bool m_IsLeft{ false };
		bool m_Visible{ true };

		void SetStartLocation(int depth, bool isLeft, const glm::vec2& offset);
		void ActivateDisc();
		bool JumpedOnDisc(std::pair<int, int> newPosition);
	};
}
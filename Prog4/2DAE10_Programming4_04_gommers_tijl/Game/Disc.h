#pragma once
#include "GameObject.h"

namespace Game
{
	class Disc : public TG::GameObject
	{
	public:
		Disc(std::shared_ptr<TG::Texture2D> textureSPTR, const glm::vec2& gridTop, const glm::vec2& offset);
		~Disc()                      = default;
		Disc(Disc&&)                 = delete;
		Disc(const Disc&)            = delete;
		Disc& operator=(Disc&&)      = delete;
		Disc& operator=(const Disc&) = delete;

		void SetStartLocation(int depth, bool isLeft, const glm::vec2& offset);
	private:
		glm::vec2 m_StartPos;
		glm::vec2 m_EndPos;
		glm::vec2 m_Direction;
		float m_HeightAbove{ 40.f };
	};
}
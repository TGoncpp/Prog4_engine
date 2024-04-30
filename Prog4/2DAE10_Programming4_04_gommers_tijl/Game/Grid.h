#pragma once
#include "Cube.h"

namespace Game
{
	class Grid final : public TG::GameObject
	{
	public:
		Grid(const glm::vec2& position, int size, std::shared_ptr<TG::Texture2D> textureSPTR);
		~Grid()                       = default;
		Grid(Grid&&)                  = delete;
		Grid(const Grid&)             = delete;
		Grid& operator= (const Grid&) = delete;
		Grid& operator= (Grid&&)      = delete;

		virtual void Render()const override;

	private:
		std::vector<std::vector<std::unique_ptr<Cube>>> m_vGrid;
	};
}
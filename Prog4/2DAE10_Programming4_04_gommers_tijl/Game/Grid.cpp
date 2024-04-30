#include "Grid.h"

Game::Grid::Grid(const glm::vec2& position, int size, std::shared_ptr<TG::Texture2D> textureSPTR)
{
	m_vGrid.resize(size);
	const glm::vec2 cubeOffset{};
	for (int outer{}; outer < size; ++outer)
	{
		std::vector<std::unique_ptr< Cube>> vLines(size);
		glm::vec2 topCubeLocation{ position  };
		(void)position;
		for (int cube{}; cube < vLines.size(); ++cube)
		{
			topCubeLocation += glm::vec2{ 20.f, 20.f };
			vLines[cube]= std::make_unique< Cube>(topCubeLocation, CubeState::startFase, textureSPTR);
		}
		m_vGrid[outer] = std::move(vLines);
	}
}

void Game::Grid::Render() const
{
	for (const auto& lines : m_vGrid)
	{
		for (const auto& cube : lines)
		{
			cube->Render();
		}
	}
}

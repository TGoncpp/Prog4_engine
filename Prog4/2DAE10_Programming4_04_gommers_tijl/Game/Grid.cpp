#include "Grid.h"
#include "Texture2D.h"


Game::Grid::Grid(const glm::vec2& position, int size, std::shared_ptr<TG::Texture2D> textureSPTR)
{
	glm::vec2 cubeOffset{ textureSPTR.get()->GetSize()};	
	cubeOffset.x /= 12.f;//colums and half because moves only half a block away
	cubeOffset.y /= 4.f;//rows and 75% off ofset on each other
	glm::vec2 startCube{ position - cubeOffset };

	m_vGrid.resize(size);
	for (int outer{}; outer < size; ++outer)
	{
		std::vector<std::unique_ptr< Cube>> vLines(size- outer);
		startCube.x -= cubeOffset.x;
		startCube.y += cubeOffset.y;
		glm::vec2 topCubeLocation{ startCube  };
		for (int cube{}; cube < vLines.size() ; ++cube)
		{
			topCubeLocation += cubeOffset;
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

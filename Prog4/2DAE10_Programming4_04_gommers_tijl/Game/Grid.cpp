#include "Grid.h"
#include "Texture2D.h"


Game::Grid::Grid(const glm::vec2& position, int size, std::shared_ptr<TG::Texture2D> textureSPTR)
	: m_CubeSize{ textureSPTR.get()->GetSize()}	
{
	m_CubeSize.x /= 12.f;//colums and half because moves only half a block away
	m_CubeSize.y /= 4.f;//rows and 75% off ofset on each other
	glm::vec2 startCube{ position - m_CubeSize };

	m_vGrid.resize(size);
	for (int outer{}; outer < size; ++outer)
	{
		std::vector<std::unique_ptr< Cube>> vLines(size- outer);
		startCube.x -= m_CubeSize.x;
		startCube.y += m_CubeSize.y;
		glm::vec2 topCubeLocation{ startCube  };
		for (int cube{}; cube < vLines.size() ; ++cube)
		{
			topCubeLocation += m_CubeSize;
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

glm::vec2 Game::Grid::GetCubeSize() const
{
	return m_CubeSize;
}

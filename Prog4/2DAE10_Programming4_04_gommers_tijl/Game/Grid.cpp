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

Game::Grid::~Grid()
{
	m_SubjectOwnrPtr->OnCubeInteraction.RemoveObserver(this);
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

void Game::Grid::Update(float time)
{
	if (!m_IsLevelFinished)return;

	for (const auto& lines : m_vGrid)
	{
		for (const auto& cube : lines)
		{
			cube->Update(time);
		}
	}
}

glm::vec2 Game::Grid::GetCubeSize() const
{
	return m_CubeSize;
}

bool Game::Grid::CheckLevelState()
{
	for (const auto& lines : m_vGrid)
	{
		for (const auto& cube : lines)
		{
			if (!cube.get()->IsFinalState())
				return false;
		}
	}

	return true;
}

void Game::Grid::SetSubject(Character* subjectToObserve)
{
	m_SubjectOwnrPtr = subjectToObserve;
	m_SubjectOwnrPtr->OnCubeInteraction.AddObserver(this);
}

void Game::Grid::OnSubjectDestroy()
{
	m_SubjectOwnrPtr = nullptr;
}

void Game::Grid::Notify(std::pair<int, int> newPosition)
{
	if (newPosition.first < 0 || newPosition.second < 0) return;
	if (newPosition.first >= m_vGrid.size() || newPosition.second >= m_vGrid[newPosition.first].size()) return;

	m_vGrid[newPosition.first][newPosition.second]->UpdateState();
	if (CheckLevelState())
	{
		m_IsLevelFinished = true;
	}
}

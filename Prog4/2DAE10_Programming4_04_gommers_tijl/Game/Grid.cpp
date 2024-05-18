#include "Grid.h"
#include "Texture2D.h"


Game::Grid::Grid(const glm::vec2& position, int size, std::shared_ptr<TG::Texture2D> textureSPTR)
	: m_CubeSize{ textureSPTR.get()->GetSize()}	
{
	m_CubeSize.x /= 12.f;//colums and half because moves only half a block away
	m_CubeSize.y /= 4.f;//rows and 75% off ofset on each other
	glm::vec2 startCube{ position - m_CubeSize };
	startCube.y -= m_CubeSize.y * 0.5f;

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
			vLines[cube] = std::make_unique< Cube>(topCubeLocation, ECubeProgressState::startFase, textureSPTR, std::make_pair<int, int>(3, 6));
		}
		m_vGrid[outer] = std::move(vLines);
	}
}

Game::Grid::~Grid()
{
	for (auto& subjects : m_vSubjectOwnrPtr)
	{
		subjects->OnCubeInteraction.RemoveObserver(this);
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
	subjectToObserve->OnCubeInteraction.AddObserver(this);
	m_vSubjectOwnrPtr.push_back( subjectToObserve);
}

void Game::Grid::OnSubjectDestroy()
{
	for (auto& subjects : m_vSubjectOwnrPtr)
	{
		subjects = nullptr;
	}
}

void Game::Grid::Notify(Character* object, bool isMoving)
{
	std::pair<int, int> newPosition = object->GetGridPosition();
	ECharacterType type             = object->GetCharacterType();

	//jumped off the platform
	if (newPosition.first < 0 || newPosition.second < 0 ||
		newPosition.first >= m_vGrid.size() || newPosition.second >= m_vGrid[newPosition.first].size())
	{
		//object->JumpOfGrid();
		OnDiscInteraction.OnNotifyAll(newPosition, object);
		return;
	}
	//remove character from the cube if moving
	if (isMoving)
	{
		m_vGrid[newPosition.first][newPosition.second]->RemoveVisiterOnCube(type);
		return;
	}
	
	
	//if valid index check-> check for collision
	m_vGrid[newPosition.first][newPosition.second]->AddVisiterOnCube(type);
	if (m_vGrid[newPosition.first][newPosition.second]->IsCollisionOnCube())
	{
		for (auto& subjects : m_vSubjectOwnrPtr)
		{
			subjects->CollisionCheck(m_vGrid[newPosition.first][newPosition.second]->GetDominantTypeOnCube(), newPosition);
		}
		if (object->IsDead())
			return;
	}

	//if red or green->update cube
	if (type == ECharacterType::purple)return;

	m_vGrid[newPosition.first][newPosition.second]->UpdateProgressState(type);
	if (CheckLevelState())
	{
		m_IsLevelFinished = true;
	}
}

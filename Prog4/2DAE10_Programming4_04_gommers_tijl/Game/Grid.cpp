#include "Grid.h"
#include "Texture2D.h"
#include "LevelRoundComponent.h"


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
		for (size_t cube{}; cube < vLines.size() ; ++cube)
		{
			topCubeLocation += m_CubeSize;
			vLines[cube] = std::make_unique< Cube>(topCubeLocation, ECubeProgressState::startFase, textureSPTR, std::make_pair<int, int>(3, 6));
			vLines[cube]->SetLvlRound(0, 1);
		}
		m_vGrid[outer] = std::move(vLines);
	}
	auto comp = AddComponent<LvlRoundComponent>(this);
	comp->OnAnim.AddObserver(this);
	comp->OnNextPhase.AddObserver(this);
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

void Game::Grid::ApplyGameMode(int )
{
	ResetGridOnSetLvlRound(1, 0);
	OnHudUpdate.OnNotifyAll(1, 0);
}

glm::vec2 Game::Grid::GetCubeSize() const
{
	return m_CubeSize;
}

bool Game::Grid::CheckLevelState()
{
	LvlRoundComponent* comp{ nullptr };
	if(CheckComponent<LvlRoundComponent>())
		comp = GetComponent<LvlRoundComponent>();

	for (const auto& lines : m_vGrid)
	{
		for (const auto& cube : lines)
		{
			if (!cube.get()->IsFinalState(comp->GetLvl()))
				return false;
		}
	}

	return true;
}

void Game::Grid::FinishAnim(float time)
{
	for (const auto& lines : m_vGrid)
	{
		for (const auto& cube : lines)
		{
			cube->Update(time);
		}
	}
}

void Game::Grid::ResetGridOnSetLvlRound(int lvl, int round)
{
	for (const auto& lines : m_vGrid)
	{
		for (const auto& cube : lines)
		{
			cube->ClearCube();
			cube->SetLvlRound(lvl, round);

		}
	}
}

void Game::Grid::SetGridSubject(Character* subjectToObserve)
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

	//remove character from the cube if moving
	if (isMoving)
	{
		m_vGrid[newPosition.first][newPosition.second]->RemoveVisiterOnCube(type);
		return;
	}
	
	//jumped off the platform - Add score if it was curly
	if (newPosition.first < 0 || newPosition.second < 0 ||
		newPosition.first >= static_cast<int>(m_vGrid.size()) || newPosition.second >= static_cast<int>(m_vGrid[newPosition.first].size()))
	{
		if (type != ECharacterType::red)
		{
			object->JumpOfGrid(true);
			if (type == ECharacterType::purple)
				object->OnScore.OnNotifyAll(ECharacterType::purple);
		}
		else
			OnDiscInteraction.OnNotifyAll(newPosition, object);
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

	LvlRoundComponent* comp = nullptr;
	if (CheckComponent<LvlRoundComponent>())
		comp = GetComponent<LvlRoundComponent>();

	//gain score points when progressing on the grid
	if (m_vGrid[newPosition.first][newPosition.second]->UpdateProgressState(type, comp->GetLvl()))
		object->OnScore.OnNotifyAll(ECharacterType::red);

	//check if all cubes are in final phase
	if (CheckLevelState() && comp)
	{
		comp->StartAnim();
	}
}

void Game::Grid::Notify(int round, int level)
{
	ResetGridOnSetLvlRound(level, round);
	OnHudUpdate.OnNotifyAll(level, round);
}

void Game::Grid::Notify(float time)
{
	FinishAnim(time);
}

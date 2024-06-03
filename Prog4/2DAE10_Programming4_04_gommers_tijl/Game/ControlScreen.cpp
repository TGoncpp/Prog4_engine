#include "ControlScreen.h"
#include "RenderComponent.h"

Game::controlScreen::controlScreen(std::vector<std::shared_ptr<TG::Texture2D>> vTextures)
	:m_vTextureSPtr{vTextures}
{
	AddComponent<TG::RenderComponent>(this, vTextures[0]);
}

void Game::controlScreen::ApplyGameMode(int gameModeValue, int)
{
	//set new images
	auto comp = GetComponent<TG::RenderComponent>();
	comp->SetTexture(m_vTextureSPtr[gameModeValue]);

}

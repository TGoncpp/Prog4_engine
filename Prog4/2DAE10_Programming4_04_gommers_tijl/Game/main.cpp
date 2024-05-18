#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "Scene.h"

#include "RenderComponent.h"
#include "healthDisplay.h"
#include "GameOverDisplay.h"
#include "ScoreDisplay.h"
#include "MovementComponent.h"
#include "HealthComponent.h"
#include "LootComponent.h"
#include <Xinput.h>
#include "ServiceLocator.h"
#include "Grid.h"
#include "NPC.h"
#include "Disc.h"

#include <iostream>

	const int WINDOW_WIDTH{ 640 }, WINDOW_HEIGHT{ 480 };

void load()
{
	const float worldScale{ 1.7f };
	const int gridSize{ 7 };
	auto& scene       = TG::SceneManager::GetInstance().CreateScene("Demo");
	auto& input       = TG::InputManager::GetInstance();
	auto font         = TG::ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
	auto largeFont    = TG::ResourceManager::GetInstance().LoadFont("Lingua.otf", 60);
	auto cubeTexture  = TG::ResourceManager::GetInstance().LoadTexture("Textures/Qbert Cubes.png", true, worldScale);
	auto QbertTexture = TG::ResourceManager::GetInstance().LoadTexture("Textures/Qbert P1 Spritesheet.png", true, worldScale, std::pair<int, int>(1,4));
	auto snakeTexture = TG::ResourceManager::GetInstance().LoadTexture("Textures/Coily Spritesheet.png", true, worldScale, std::pair<int, int>(1, 10));
	auto samTexture   = TG::ResourceManager::GetInstance().LoadTexture("Textures/Slick Sam Spritesheet.png", true, worldScale, std::pair<int, int>(2, 2));
	auto DiscTexture   = TG::ResourceManager::GetInstance().LoadTexture("Textures/Disk Spritesheet.png", true, worldScale, std::pair<int, int>(1, 30));
	//if NDEBUG
	TG::Locator::provide(std::make_unique< TG::GameAudio>());
	//Else 
	//TG::Locator::provide(std::make_unique< TG::LoggedAudio>());
	
	//TG::Locator::getAudio().playSound("Level");

	//Create Background object
	auto go = std::make_unique<TG::GameObject>();
	go->AddComponent<TG::RenderComponent>(go.get(), "Textures/background.tga");

	const glm::vec2 topCubePosition{ glm::vec2{ WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 5.f } };
	auto grid = std::make_unique<Game::Grid>(topCubePosition, gridSize , cubeTexture);
	const glm::vec2 cubeSize{ grid->GetCubeSize() };

	auto character = std::make_unique<Game::Character>(topCubePosition, QbertTexture, cubeSize);
	grid->SetGridSubject(character.get());

	auto npc = std::make_unique<Game::NPC>(topCubePosition, snakeTexture, cubeSize, Game::ECharacterType::purple);
	npc.get()->SetPositionOnGridByIndex(2, 2, cubeSize);
	grid->SetGridSubject(npc.get());
	npc->UpdateGrid(false);
	
	auto npcGreen = std::make_unique<Game::NPC>(topCubePosition, samTexture, cubeSize, Game::ECharacterType::green);
	npcGreen.get()->SetPositionOnGridByIndex(3, 1, cubeSize);
	grid->SetGridSubject(npcGreen.get());
	npcGreen->UpdateGrid(false);

	auto disc = std::make_unique<Game::Disc>(DiscTexture, topCubePosition, cubeSize);
	disc->SetGridSubject(grid.get());
	auto disc2 = std::make_unique<Game::Disc>(DiscTexture, topCubePosition, cubeSize);
	disc2->SetGridSubject(grid.get());

	//InfoScreen
	auto IS = std::make_unique<TG::GameObject>();
	IS.get()->AddComponent<TG::TextComponent>(IS.get(), "Use WASD to move Snake around to inflict damage to red on contact", font);
	IS.get()->AddComponent<TG::TextComponent>(IS.get(), "Use Arrows to move red around, get points by killing the green character", font, glm::vec3{ 0.f, 20.f, 0.f });
	IS->SetLocalPosition(5, 440);

	

	//----------------------------------------------------
	//INPUT BINDING
	//---------------------------------------------------
	//inputMapping Character 1
	auto moveUp = std::make_unique<TG::Move>(character.get(), glm::vec2{0.f, 1.f});
	input.InputBinding(std::move(moveUp), SDL_SCANCODE_UP, EInputType::pressed);
	auto moveDown = std::make_unique<TG::Move>(character.get(), glm::vec2{ 0.f, -1.f });
	input.InputBinding(std::move(moveDown), SDL_SCANCODE_DOWN, EInputType::pressed);
	auto moveRight = std::make_unique<TG::Move>(character.get(), glm::vec2{ 1.f, 0.f });
	input.InputBinding(std::move(moveRight), SDL_SCANCODE_RIGHT, EInputType::pressed);
	auto moveLeft = std::make_unique<TG::Move>(character.get(), glm::vec2{ -1.f, 0.f });
	input.InputBinding(std::move(moveLeft), SDL_SCANCODE_LEFT, EInputType::pressed);

	//inputMapping Snake
	auto moveUpSnail = std::make_unique<TG::Move>(npc.get(), glm::vec2{ 0.f, 1.f });
	input.InputBinding(std::move(moveUpSnail), SDL_SCANCODE_W, EInputType::pressed);
	auto moveDownSnail = std::make_unique<TG::Move>(npc.get(), glm::vec2{ 0.f, -1.f });
	input.InputBinding(std::move(moveDownSnail), SDL_SCANCODE_S, EInputType::pressed);
	auto moveRightSnail = std::make_unique<TG::Move>(npc.get(), glm::vec2{ 1.f, 0.f });
	input.InputBinding(std::move(moveRightSnail), SDL_SCANCODE_D, EInputType::pressed);
	auto moveLeftSnail = std::make_unique<TG::Move>(npc.get(), glm::vec2{ -1.f, 0.f });
	input.InputBinding(std::move(moveLeftSnail), SDL_SCANCODE_A, EInputType::pressed);


	//----------------------------------------------------
	//Add to scene
	//----------------------------------------------------

	scene.Add(std::move(go));
	scene.Add(std::move(grid));
	scene.Add(std::move(disc));
	scene.Add(std::move(disc2));
	scene.Add(std::move(character));
	scene.Add(std::move(npc));
	scene.Add(std::move(npcGreen));
	scene.Add(std::move(IS));
		
	
	////Character 2
	////inputMapping
	//auto moveUp2 = std::make_unique<TG::Move>(scene.GetObjectByIndex(5), glm::vec2{ 0.f, -1.f });
	//input.InputBinding(std::move(moveUp2), XINPUT_GAMEPAD_DPAD_UP, EInputType::hold, true);
	//auto moveDown2 = std::make_unique<TG::Move>(scene.GetObjectByIndex(5), glm::vec2{ 0.f, 1.f });
	//input.InputBinding(std::move(moveDown2), XINPUT_GAMEPAD_DPAD_DOWN, EInputType::hold, true);
	//auto moveRight2 = std::make_unique<TG::Move>(scene.GetObjectByIndex(5), glm::vec2{ 1.f, 0.f });
	//input.InputBinding(std::move(moveRight2), XINPUT_GAMEPAD_DPAD_RIGHT, EInputType::hold, true);
	//auto moveLeft2 = std::make_unique<TG::Move>(scene.GetObjectByIndex(5), glm::vec2{ -1.f, 0.f });
	//input.InputBinding(std::move(moveLeft2), XINPUT_GAMEPAD_DPAD_LEFT, EInputType::hold, true);
	
}

int main(int, char* [])
{

	TG::Minigin engine("../Data/", WINDOW_WIDTH, WINDOW_HEIGHT);
	engine.Run(load);

	return 0;
}
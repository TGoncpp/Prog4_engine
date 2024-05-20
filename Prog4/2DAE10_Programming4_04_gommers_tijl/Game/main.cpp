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
#include "GameOverDisplay.h"
#include "ScoreDisplay.h"
#include "MovementComponent.h"
#include "HealthComponent.h"
#include "LootComponent.h"
#include <Xinput.h>
#include "ServiceLocator.h"
#include "Grid.h"
#include "NPC.h"
#include "QbertCharacter.h"
#include "Disc.h"
#include "Hud.h"

#include "time.h"
#include <iostream>

	const int WINDOW_WIDTH{ 640 }, WINDOW_HEIGHT{ 480 };

void load()
{
	const float worldScale{ 1.7f };
	const float titleScale{ 1.f };
	const int gridSize{ 7 };
	//auto& scene       = TG::SceneManager::GetInstance().CreateScene("Demo");
	auto& scene       = TG::SceneManager::GetInstance().CreateScene(TG::EMenuState::game);
	auto& input       = TG::InputManager::GetInstance();
	auto font         = TG::ResourceManager::GetInstance().LoadFont("Textures/Minecraft.ttf", 16);
	auto largeFont    = TG::ResourceManager::GetInstance().LoadFont("Textures/Minecraft.ttf", 60);
	auto cubeTexture  = TG::ResourceManager::GetInstance().LoadTexture("Textures/Qbert Cubes.png", true, worldScale);
	auto CurseTexture = TG::ResourceManager::GetInstance().LoadTexture("Textures/Qbert Curses.png", true, titleScale);
	auto QbertTexture = TG::ResourceManager::GetInstance().LoadTexture("Textures/Qbert P1 Spritesheet.png", true, worldScale, std::pair<int, int>(1,4));
	auto snakeTexture = TG::ResourceManager::GetInstance().LoadTexture("Textures/Coily Spritesheet.png", true, worldScale, std::pair<int, int>(1, 10));
	auto samTexture   = TG::ResourceManager::GetInstance().LoadTexture("Textures/Slick Sam Spritesheet.png", true, worldScale, std::pair<int, int>(2, 2));
	auto DiscTexture  = TG::ResourceManager::GetInstance().LoadTexture("Textures/Disk Spritesheet.png", true, worldScale, std::pair<int, int>(1, 30));
	auto background   = TG::ResourceManager::GetInstance().LoadTexture("Textures/background.tga", true, worldScale);
	auto lvlTexture   = TG::ResourceManager::GetInstance().LoadTexture("Textures/Level 01 Title.png", true, worldScale);
	auto cubeIndTexture= TG::ResourceManager::GetInstance().LoadTexture("Textures/Color Icons Spritesheet.png", true, 1.5f, std::pair<int, int>(2, 6));
	auto HealthTexture= TG::ResourceManager::GetInstance().LoadTexture("Textures/Heart.png", true, worldScale);
	//Menus
	auto MenuIntroTexture= TG::ResourceManager::GetInstance().LoadTexture("Textures/intro.png", true, 2.8f);
	auto MenuLvlTexture  = TG::ResourceManager::GetInstance().LoadTexture("Textures/Level 01 Title.png", true, titleScale);
	//if NDEBUG
	TG::Locator::provide(std::make_unique< TG::GameAudio>());
	//Else 
	//TG::Locator::provide(std::make_unique< TG::LoggedAudio>());
	
	//TG::Locator::getAudio().playSound("Level");

	const glm::vec2 topCubePosition{ glm::vec2{ WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 5.f } };
	auto grid = std::make_unique<Game::Grid>(topCubePosition, gridSize , cubeTexture);
	const glm::vec2 cubeSize{ grid->GetCubeSize() };

	auto character = std::make_unique<Game::QbertCharacter>(topCubePosition, QbertTexture, cubeSize, CurseTexture);
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
	auto disc1 = std::make_unique<Game::Disc>(DiscTexture, topCubePosition, cubeSize);
	disc1->SetGridSubject(grid.get());
	auto disc12 = std::make_unique<Game::Disc>(DiscTexture, topCubePosition, cubeSize);
	disc12->SetGridSubject(grid.get());

	auto vChar = std::vector<Game::Character*>{character.get(), npc.get(), npcGreen.get()};
	auto vTex = std::vector<std::shared_ptr<TG::Texture2D>>{background, HealthTexture, cubeIndTexture};
	auto hud = std::make_unique<Game::Hud>(vChar, vTex, font);
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

	scene.Add(std::move(hud));
	scene.Add(std::move(grid));
	scene.Add(std::move(disc));
	scene.Add(std::move(disc2));
	scene.Add(std::move(disc1));
	scene.Add(std::move(disc12));
	scene.Add(std::move(character));
	scene.Add(std::move(npc));
	scene.Add(std::move(npcGreen));
		
	//----------------------------------------------------
	//INTROSCENE
	//-----------------------------------------------
	auto& IntroScene = TG::SceneManager::GetInstance().CreateScene(TG::EMenuState::intro);
	auto introTexture = std::make_unique<TG::GameObject>();
	introTexture->AddComponent<TG::RenderComponent>(introTexture.get(), MenuIntroTexture);
	introTexture->AddComponent<TG::TextComponent>(introTexture.get(), "Press SPACE ", largeFont, glm::vec3 {80.f, 400.f, 0.f});

	auto enter = std::make_unique<TG::Enter>(introTexture.get());
	input.InputBinding(std::move(enter), SDL_SCANCODE_SPACE, EInputType::pressed);

	IntroScene.Add(std::move(introTexture));

	//----------------------------------------------------
	//INTERMEDIATE SCENE
	//-----------------------------------------------
	auto& InterScene = TG::SceneManager::GetInstance().CreateScene(TG::EMenuState::intermediate);
	auto interTexture = std::make_unique<TG::GameObject>();
	interTexture->AddComponent<TG::RenderComponent>(interTexture.get(), MenuLvlTexture);
	interTexture->SetLocalPosition(glm::vec2{ 75.f, 50.f });

	InterScene.Add(std::move(interTexture));

	TG::SceneManager::GetInstance().CreateMenu();
	
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
	srand(static_cast<uint32_t>(time(NULL)));
	TG::Minigin engine("../Data/", WINDOW_WIDTH, WINDOW_HEIGHT);
	engine.Run(load);

	return 0;
}
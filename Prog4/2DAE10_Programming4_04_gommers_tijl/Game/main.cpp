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
#include "TextObject.h"
#include "Scene.h"

#include "RenderComponent.h"
#include "healthDisplay.h"
#include "GameOverDisplay.h"
#include "ScoreDisplay.h"
#include "FPSComponent.h"
#include "MovementComponent.h"
#include "HealthComponent.h"
#include "LootComponent.h"
#include <Xinput.h>
#include "ServiceLocator.h"
//#include "SpriteComponent.h"
#include "Grid.h"
#include "Character.h"

#include <iostream>

	const int WINDOW_WIDTH{ 640 }, WINDOW_HEIGHT{ 480 };

void load()
{
	auto& scene = TG::SceneManager::GetInstance().CreateScene("Demo");
	auto& input = TG::InputManager::GetInstance();
	auto font = TG::ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
	auto largeFont = TG::ResourceManager::GetInstance().LoadFont("Lingua.otf", 60);
	auto cubeTexture = TG::ResourceManager::GetInstance().LoadTexture("Textures/Qbert Cubes.png", true);
	auto QbertTexture = TG::ResourceManager::GetInstance().LoadTexture("Textures/Qbert P1 Spritesheet.png", true);
	//if NDEBUG
	TG::Locator::provide(std::make_unique< TG::GameAudio>());
	//Else 
	//TG::Locator::provide(std::make_unique< TG::LoggedAudio>());
	
	//TG::Locator::getAudio().playSound("Level");

	//Create Background object
	auto go = std::make_unique<TG::GameObject>();
	go->AddComponent<TG::RenderComponent>(go.get(), "Textures/background.tga");
	scene.Add(std::move(go));

	const int gridSize{ 6 };
	const glm::vec2 topCubePosition{ glm::vec2{ WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 3.f } };

	auto grid = std::make_unique<Game::Grid>(topCubePosition, gridSize , cubeTexture);
	const glm::vec2 cubeSize{ grid->GetCubeSize() };

	auto character = std::make_unique<Game::Character>(topCubePosition, QbertTexture, cubeSize, gridSize);
	grid->SetSubject(character.get());


	//InfoScreen
	auto IS = std::make_unique<TG::GameObject>();
	IS.get()->AddComponent<TG::TextComponent>(IS.get(), "Use D-Pad to move Alex around, A to inflict damage, XYB to collect different loot", font);
	IS.get()->AddComponent<TG::TextComponent>(IS.get(), "Use Arrows to move Tom around, SPACE to inflict damage, QWE to collect different loot", font, glm::vec3{ 0.f, 20.f, 0.f });
	IS->SetLocalPosition(5, 400);

	//Add to scene
	scene.Add(std::move(grid));
	scene.Add(std::move(character));
	scene.Add(std::move(IS));
		
	

	//----------------------------------------------------
	//INPUT BINDING
	//---------------------------------------------------
	//inputMapping Character 1
	auto moveUp = std::make_unique<TG::Move>(scene.GetObjectByIndex(2), glm::vec2{ 0.f, 1.f });
	input.InputBinding(std::move(moveUp), SDL_SCANCODE_UP, EInputType::hold);
	auto moveDown = std::make_unique<TG::Move>(scene.GetObjectByIndex(2), glm::vec2{ 0.f, -1.f });
	input.InputBinding(std::move(moveDown), SDL_SCANCODE_DOWN, EInputType::hold);
	auto moveRight = std::make_unique<TG::Move>(scene.GetObjectByIndex(2), glm::vec2{ 1.f, 0.f });
	input.InputBinding(std::move(moveRight), SDL_SCANCODE_RIGHT, EInputType::hold);
	auto moveLeft = std::make_unique<TG::Move>(scene.GetObjectByIndex(2), glm::vec2{ -1.f, 0.f });
	input.InputBinding(std::move(moveLeft), SDL_SCANCODE_LEFT, EInputType::hold);
	//ActionInput
	auto PickUpDirt = std::make_unique<TG::PickUp>(scene.GetObjectByIndex(2), TG::LootType::dirt);
	input.InputBinding(std::move(PickUpDirt), SDL_SCANCODE_Q, EInputType::pressed, false);
	auto PickUpSilver = std::make_unique<TG::PickUp>(scene.GetObjectByIndex(2), TG::LootType::silver);
	input.InputBinding(std::move(PickUpSilver), SDL_SCANCODE_W, EInputType::pressed, false);
	auto PickUpGold = std::make_unique<TG::PickUp>(scene.GetObjectByIndex(2), TG::LootType::gold);
	input.InputBinding(std::move(PickUpGold), SDL_SCANCODE_E, EInputType::pressed, false);
	//auto hit = std::make_unique<TG::Hit>(scene.GetObjectByIndex(2), scene.GetObjectByIndex(5));
	//input.InputBinding(std::move(hit), SDL_SCANCODE_SPACE, EInputType::pressed, false);

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
	////ActionInput
	//PickUpDirt = std::make_unique<TG::PickUp>(scene.GetObjectByIndex(5), TG::LootType::dirt);
	//input.InputBinding(std::move(PickUpDirt), XINPUT_GAMEPAD_X, EInputType::pressed, true);
	//PickUpSilver = std::make_unique<TG::PickUp>(scene.GetObjectByIndex(5), TG::LootType::silver);
	//input.InputBinding(std::move(PickUpSilver), XINPUT_GAMEPAD_Y, EInputType::pressed, true);
	//PickUpGold = std::make_unique<TG::PickUp>(scene.GetObjectByIndex(5), TG::LootType::gold);
	//input.InputBinding(std::move(PickUpGold), XINPUT_GAMEPAD_B, EInputType::pressed, true);
	//hit = std::make_unique<TG::Hit>(scene.GetObjectByIndex(5), scene.GetObjectByIndex(2));
	//input.InputBinding(std::move(hit), XINPUT_GAMEPAD_A, EInputType::pressed, true);


}

int main(int, char* [])
{

	TG::Minigin engine("../Data/", WINDOW_WIDTH, WINDOW_HEIGHT);
	engine.Run(load);

	return 0;
}
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

#include <iostream>

	const int WINDOW_WIDTH{ 640 }, WINDOW_HEIGHT{ 480 };

void load()
{
	auto& scene = TG::SceneManager::GetInstance().CreateScene("Demo");
	auto& input = TG::InputManager::GetInstance();
	auto font = TG::ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
	auto largeFont = TG::ResourceManager::GetInstance().LoadFont("Lingua.otf", 60);
	auto cubeTexture = TG::ResourceManager::GetInstance().LoadTexture("Textures/Qbert Cubes.png", true);
	//if NDEBUG
	TG::Locator::provide(std::make_unique< TG::GameAudio>());
	//Else 
	//TG::Locator::provide(std::make_unique< TG::LoggedAudio>());
	
	//TG::Locator::getAudio().playSound("Level");

	//Create Background object
	auto go = std::make_unique<TG::GameObject>();
	go->AddComponent<TG::RenderComponent>(go.get(), "Textures/background.tga");
	scene.Add(std::move(go));
	int sceneInd{ 0 };

	auto grid = std::make_unique<Game::Grid>(glm::vec2{ WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 3.f },6 , cubeTexture);
	scene.Add(std::move(grid));

	//Create character object
	int CharcterHealth{ 3 };
	go = std::make_unique<TG::GameObject>("Tom");
	go.get()->AddComponent<TG::RenderComponent>(go.get(), "Textures/Qbert-P1.tga");
	go.get()->AddComponent<TG::MovementComponent>(go.get(), 50.f);
	go.get()->AddComponent<TG::HealthComponent>(go.get(), CharcterHealth);
	go.get()->AddComponent<TG::LootComponent>(go.get());
	go->SetLocalPosition(216, 180);
	
	scene.Add(std::move(go));
	sceneInd = 1;
	
	//Create player 1 healt image object
	auto to = std::make_unique<TG::GameObject>();
	to->AddComponent<TG::TextComponent>(to.get(), "", font);
	to->AddComponent<TG::HealthDisplay>(to.get(), scene.GetObjectByIndex(2));
	to->SetLocalPosition(5, 20);
	scene.Add(std::move(to));
	sceneInd = 2;
	
	//Create player 1 score image object
	to = std::make_unique<TG::GameObject>();
	to->AddComponent<TG::TextComponent>(to.get(), "", font);
	to->AddComponent<TG::ScoreDisplay>(to.get(), scene.GetObjectByIndex(2));
	to->SetLocalPosition(5, 40);
	scene.Add(std::move(to));
	sceneInd = 3;
	
	//Create character2 object
	auto go2 = std::make_unique<TG::GameObject>("Alex");
	go2.get()->AddComponent<TG::RenderComponent>(go2.get(), "Textures/Qbert-P2.tga");
	go2.get()->AddComponent<TG::MovementComponent>(go2.get(), 100.f);
	go2.get()->AddComponent<TG::HealthComponent>(go2.get(), CharcterHealth);
	go2.get()->AddComponent<TG::LootComponent>(go2.get());
	
	go2->SetLocalPosition(WINDOW_WIDTH / 2.f, 200);
	scene.Add(std::move(go2));
	sceneInd = 4;
	
	//Create player 2 healt image object
	auto to2 = std::make_unique<TG::GameObject>();
	to2->AddComponent<TG::TextComponent>(to2.get(), "", font);
	to2->AddComponent<TG::HealthDisplay>(to2.get(), scene.GetObjectByIndex(5));
	to2->SetLocalPosition(5, 60);
	scene.Add(std::move(to2));
	sceneInd = 5;
	
	
	//Create player 2 Score image object
	to2 = std::make_unique<TG::GameObject>();
	to2->AddComponent<TG::TextComponent>(to2.get(), "", font);
	to2->AddComponent<TG::ScoreDisplay>(to2.get(), scene.GetObjectByIndex(5));
	to2->SetLocalPosition(5, 80);
	scene.Add(std::move(to2));
	sceneInd = 6;
	
	
	//Create FPS object
	auto fps = std::make_unique<TG::GameObject>();
	fps.get()->AddComponent<TG::TextComponent>(fps.get(), "0000.000FPS", font);
	fps.get()->AddComponent<TG::FPSComponent>(fps.get());
	fps->SetLocalPosition(200, 5);
	scene.Add(std::move(fps));
	sceneInd = 7;
	
	//Gameover screen
	auto GO = std::make_unique<TG::GameObject>();
	GO.get()->AddComponent<TG::TextComponent>(GO.get(), "", largeFont);
	GO.get()->AddComponent<TG::GameOverDisplay>(GO.get(), std::vector<TG::GameObject*>{ scene.GetObjectByIndex(5), scene.GetObjectByIndex(2) });
	GO->SetLocalPosition(5, 200);
	scene.Add(std::move(GO));
	sceneInd = 8;
	
	//InfoScreen
	auto IS = std::make_unique<TG::GameObject>();
	IS.get()->AddComponent<TG::TextComponent>(IS.get(), "Use D-Pad to move Alex around, A to inflict damage, XYB to collect different loot", font);
	IS.get()->AddComponent<TG::TextComponent>(IS.get(), "Use Arrows to move Tom around, SPACE to inflict damage, QWE to collect different loot", font, glm::vec3{ 0.f, 20.f, 0.f });
	IS->SetLocalPosition(5, 400);
	scene.Add(std::move(IS));
	sceneInd = 9;

	

	//----------------------------------------------------
	//INPUT BINDING
	//---------------------------------------------------
	//inputMapping Character 1
	auto moveUp = std::make_unique<TG::Move>(scene.GetObjectByIndex(2), glm::vec2{ 0.f, -1.f });
	input.InputBinding(std::move(moveUp), SDL_SCANCODE_UP, EInputType::hold);
	auto moveDown = std::make_unique<TG::Move>(scene.GetObjectByIndex(2), glm::vec2{ 0.f, 1.f });
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
	auto hit = std::make_unique<TG::Hit>(scene.GetObjectByIndex(2), scene.GetObjectByIndex(5));
	input.InputBinding(std::move(hit), SDL_SCANCODE_SPACE, EInputType::pressed, false);

	//Character 2
	//inputMapping
	auto moveUp2 = std::make_unique<TG::Move>(scene.GetObjectByIndex(5), glm::vec2{ 0.f, -1.f });
	input.InputBinding(std::move(moveUp2), XINPUT_GAMEPAD_DPAD_UP, EInputType::hold, true);
	auto moveDown2 = std::make_unique<TG::Move>(scene.GetObjectByIndex(5), glm::vec2{ 0.f, 1.f });
	input.InputBinding(std::move(moveDown2), XINPUT_GAMEPAD_DPAD_DOWN, EInputType::hold, true);
	auto moveRight2 = std::make_unique<TG::Move>(scene.GetObjectByIndex(5), glm::vec2{ 1.f, 0.f });
	input.InputBinding(std::move(moveRight2), XINPUT_GAMEPAD_DPAD_RIGHT, EInputType::hold, true);
	auto moveLeft2 = std::make_unique<TG::Move>(scene.GetObjectByIndex(5), glm::vec2{ -1.f, 0.f });
	input.InputBinding(std::move(moveLeft2), XINPUT_GAMEPAD_DPAD_LEFT, EInputType::hold, true);
	//ActionInput
	PickUpDirt = std::make_unique<TG::PickUp>(scene.GetObjectByIndex(5), TG::LootType::dirt);
	input.InputBinding(std::move(PickUpDirt), XINPUT_GAMEPAD_X, EInputType::pressed, true);
	PickUpSilver = std::make_unique<TG::PickUp>(scene.GetObjectByIndex(5), TG::LootType::silver);
	input.InputBinding(std::move(PickUpSilver), XINPUT_GAMEPAD_Y, EInputType::pressed, true);
	PickUpGold = std::make_unique<TG::PickUp>(scene.GetObjectByIndex(5), TG::LootType::gold);
	input.InputBinding(std::move(PickUpGold), XINPUT_GAMEPAD_B, EInputType::pressed, true);
	hit = std::make_unique<TG::Hit>(scene.GetObjectByIndex(5), scene.GetObjectByIndex(2));
	input.InputBinding(std::move(hit), XINPUT_GAMEPAD_A, EInputType::pressed, true);


}

int main(int, char* [])
{

	TG::Minigin engine("../Data/", WINDOW_WIDTH, WINDOW_HEIGHT);
	engine.Run(load);

	return 0;
}
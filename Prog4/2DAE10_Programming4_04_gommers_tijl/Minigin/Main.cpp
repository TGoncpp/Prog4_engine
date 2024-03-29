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

//#include <steam_api.h>
#include <iostream>


void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	auto& input = dae::InputManager::GetInstance();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
	auto largeFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 60);


	//Create Background object
	auto go = std::make_unique<dae::GameObject>();
	go->AddComponent<TG::RenderComponent>(go.get(), "background.tga");
	scene.Add(std::move(go));
	int sceneInd{ 0 };

	//Create character object
	int CharcterHealth{ 3 };
	go = std::make_unique<dae::GameObject>("Tom");
	go.get()->AddComponent<TG::RenderComponent>(go.get(), "Qbert-P1.tga");	
	go.get()->AddComponent<TG::MovementComponent>(go.get(), 50.f);	
	go.get()->AddComponent<TG::HealthComponent>(go.get(), CharcterHealth);	
	go.get()->AddComponent<TG::LootComponent>(go.get());	
	go->SetLocalPosition(216, 180);
	
	scene.Add(std::move(go));
	sceneInd = 1;

	//Create player 1 healt image object
	auto to = std::make_unique<dae::GameObject>();
	to->AddComponent<TG::TextComponent>(to.get(), "", font);
	to->AddComponent<TG::HealthDisplay>(to.get(), scene.GetObjectByIndex(1));
	to->SetLocalPosition(5, 20);
	scene.Add(std::move(to));
	sceneInd = 2;

	//Create player 1 score image object
	to = std::make_unique<dae::GameObject>();
	to->AddComponent<TG::TextComponent>(to.get(), "", font);
	to->AddComponent<TG::ScoreDisplay>(to.get(), scene.GetObjectByIndex(1));
	to->SetLocalPosition(5, 40);
	scene.Add(std::move(to));
	sceneInd = 3;

	//Create character2 object
	auto go2 = std::make_unique<dae::GameObject>("Alex");
	go2.get()->AddComponent<TG::RenderComponent>(go2.get(), "Qbert-P2.tga");	
	go2.get()->AddComponent<TG::MovementComponent>(go2.get(), 100.f);	
	go2.get()->AddComponent<TG::HealthComponent>(go2.get(), CharcterHealth);	
	go2.get()->AddComponent<TG::LootComponent>(go2.get());	
	
	go2->SetLocalPosition(216, 200);
	scene.Add(std::move(go2));
	sceneInd = 4;

	//Create player 2 healt image object
	auto to2 = std::make_unique<dae::GameObject>();
	to2->AddComponent<TG::TextComponent>(to2.get(), "", font);
	to2->AddComponent<TG::HealthDisplay>(to2.get(), scene.GetObjectByIndex(4));
	to2->SetLocalPosition(5, 60);
	scene.Add(std::move(to2));
	sceneInd = 5;


	//Create player 2 Score image object
	to2 = std::make_unique<dae::GameObject>();
	to2->AddComponent<TG::TextComponent>(to2.get(), "", font);
	to2->AddComponent<TG::ScoreDisplay>(to2.get(), scene.GetObjectByIndex(4));
	to2->SetLocalPosition(5, 80);
	scene.Add(std::move(to2));
	sceneInd = 6;


	//Create FPS object
	auto fps = std::make_unique<dae::GameObject>();
	fps.get()->AddComponent<TG::TextComponent>(fps.get(), "0000.000FPS", font);
	fps.get()->AddComponent<TG::FPSComponent>(fps.get());
	fps->SetLocalPosition(200, 5);
	scene.Add(std::move(fps));
	sceneInd = 7;

	//Gameover screen
	auto GO = std::make_unique<dae::GameObject>();
	GO.get()->AddComponent<TG::TextComponent>(GO.get(), "", largeFont);
	GO.get()->AddComponent<TG::GameOverDisplay>(GO.get(), std::vector<dae::GameObject*>{ scene.GetObjectByIndex(4), scene.GetObjectByIndex(1) });
	GO->SetLocalPosition(5, 200);
	scene.Add(std::move(GO));
	sceneInd = 8;

	//InfoScreen
	auto IS = std::make_unique<dae::GameObject>();
	IS.get()->AddComponent<TG::TextComponent>(IS.get(), "Use D-Pad to move Alex around, A to inflict damage, XYB to collect different loot", font);
	IS.get()->AddComponent<TG::TextComponent>(IS.get(), "Use Arrows to move Tom around, SPACE to inflict damage, QWE to collect different loot", font, glm::vec3{0.f, 20.f, 0.f});
	IS->SetLocalPosition(5, 400);
	scene.Add(std::move(IS));
	sceneInd = 9;

	//----------------------------------------------------
	//INPUT BINDING
	//---------------------------------------------------
	//inputMapping Character 1
	auto moveUp = std::make_unique<dae::Move>(scene.GetObjectByIndex(1), glm::vec2{0.f, -1.f});
	input.InputBinding(std::move(moveUp), SDL_SCANCODE_UP, EInputType::hold);
	auto moveDown = std::make_unique<dae::Move>(scene.GetObjectByIndex(1), glm::vec2{ 0.f, 1.f });
	input.InputBinding(std::move(moveDown), SDL_SCANCODE_DOWN, EInputType::hold);
	auto moveRight = std::make_unique<dae::Move>(scene.GetObjectByIndex(1), glm::vec2{ 1.f, 0.f });
	input.InputBinding(std::move(moveRight), SDL_SCANCODE_RIGHT, EInputType::hold);
	auto moveLeft = std::make_unique<dae::Move>(scene.GetObjectByIndex(1), glm::vec2{ -1.f, 0.f });
	input.InputBinding(std::move(moveLeft), SDL_SCANCODE_LEFT, EInputType::hold);
	//ActionInput
	auto PickUpDirt = std::make_unique<dae::PickUp>(scene.GetObjectByIndex(1), TG::LootType::dirt);
	input.InputBinding(std::move(PickUpDirt), SDL_SCANCODE_Q, EInputType::pressed, false);
	auto PickUpSilver = std::make_unique<dae::PickUp>(scene.GetObjectByIndex(1), TG::LootType::silver);
	input.InputBinding(std::move(PickUpSilver), SDL_SCANCODE_W, EInputType::pressed, false);
	auto PickUpGold = std::make_unique<dae::PickUp>(scene.GetObjectByIndex(1), TG::LootType::gold);
	input.InputBinding(std::move(PickUpGold), SDL_SCANCODE_E, EInputType::pressed, false);
	auto hit = std::make_unique<dae::Hit>(scene.GetObjectByIndex(1), scene.GetObjectByIndex(4));
	input.InputBinding(std::move(hit), SDL_SCANCODE_SPACE, EInputType::pressed, false);

	//Character 2
	//inputMapping
	auto moveUp2 = std::make_unique<dae::Move>(scene.GetObjectByIndex(4), glm::vec2{ 0.f, -1.f });
	input.InputBinding(std::move(moveUp2), XINPUT_GAMEPAD_DPAD_UP, EInputType::hold, true);
	auto moveDown2 = std::make_unique<dae::Move>(scene.GetObjectByIndex(4), glm::vec2{ 0.f, 1.f });
	input.InputBinding(std::move(moveDown2), XINPUT_GAMEPAD_DPAD_DOWN, EInputType::hold, true);
	auto moveRight2 = std::make_unique<dae::Move>(scene.GetObjectByIndex(4), glm::vec2{ 1.f, 0.f });
	input.InputBinding(std::move(moveRight2), XINPUT_GAMEPAD_DPAD_RIGHT, EInputType::hold, true);
	auto moveLeft2 = std::make_unique<dae::Move>(scene.GetObjectByIndex(4), glm::vec2{ -1.f, 0.f });
	input.InputBinding(std::move(moveLeft2), XINPUT_GAMEPAD_DPAD_LEFT, EInputType::hold, true);
	//ActionInput
	PickUpDirt = std::make_unique<dae::PickUp>(scene.GetObjectByIndex(4), TG::LootType::dirt);
	input.InputBinding(std::move(PickUpDirt), XINPUT_GAMEPAD_X, EInputType::pressed, true);
	PickUpSilver = std::make_unique<dae::PickUp>(scene.GetObjectByIndex(4), TG::LootType::silver);
	input.InputBinding(std::move(PickUpSilver), XINPUT_GAMEPAD_Y, EInputType::pressed, true);
	PickUpGold = std::make_unique<dae::PickUp>(scene.GetObjectByIndex(4), TG::LootType::gold);
	input.InputBinding(std::move(PickUpGold), XINPUT_GAMEPAD_B, EInputType::pressed, true);
	hit = std::make_unique<dae::Hit>(scene.GetObjectByIndex(4), scene.GetObjectByIndex(1));
	input.InputBinding(std::move(hit), XINPUT_GAMEPAD_A, EInputType::pressed, true);


}

int main(int , char* []) 
{
	if (!SteamAPI_Init())
	{
		std::cerr << "Fatal Error - Steam must be running to play this game (SteamAPI_Init() failed)." << std::endl;
		return 1;
	}
	else
	{
		std::cout << "Succesfully initialised steam\n";
		//g_SteamAchievements = new CSteamAchievements(g_Achievements, 4);
	}

	dae::Minigin engine("../Data/");
	engine.Run(load);

	SteamAPI_Shutdown();
	/*if (g_SteamAchievements)
		delete g_SteamAchievements;*/
    return 0;
}
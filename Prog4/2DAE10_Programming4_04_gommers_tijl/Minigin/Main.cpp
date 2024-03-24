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
#include "FPSComponent.h"
#include "MovementComponent.h"
#include "HealthComponent.h"
#include <Xinput.h>




void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	auto& input = dae::InputManager::GetInstance();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);


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
	go->SetLocalPosition(216, 180);
	//inputMapping
	auto moveUp = std::make_unique<dae::MoveUp>( go.get());
	input.InputBinding(std::move(moveUp), SDL_SCANCODE_UP, EInputType::hold);
	auto moveDown = std::make_unique<dae::MoveDown>( go.get());
	input.InputBinding(std::move(moveDown), SDL_SCANCODE_DOWN, EInputType::hold);
	auto moveRight = std::make_unique<dae::MoveRight>( go.get());
	input.InputBinding(std::move(moveRight), SDL_SCANCODE_RIGHT, EInputType::hold);
	auto moveLeft = std::make_unique<dae::MoveLeft>( go.get());
	input.InputBinding(std::move(moveLeft), SDL_SCANCODE_LEFT, EInputType::hold);

	scene.Add(std::move(go));
	sceneInd = 1;

	//Create player 1 healt image object
	auto to = std::make_unique<dae::GameObject>();
	to->AddComponent<TG::TextComponent>(to.get(), "", font);
	to->AddComponent<TG::HealthDisplay>(to.get(), scene.GetObjectByIndex(1));
	to->SetLocalPosition(5, 20);
	scene.Add(std::move(to));
	sceneInd = 2;

	//Create character2 object
	auto go2 = std::make_unique<dae::GameObject>("Alex");
	go2.get()->AddComponent<TG::RenderComponent>(go2.get(), "Qbert-P2.tga");	
	go2.get()->AddComponent<TG::MovementComponent>(go2.get(), 100.f);	
	go2.get()->AddComponent<TG::HealthComponent>(go2.get(), CharcterHealth);	
	//inputMapping
	auto moveUp2 = std::make_unique<dae::MoveUp>(go2.get());
	input.InputBinding(std::move(moveUp2), XINPUT_GAMEPAD_DPAD_UP, EInputType::hold, true);
	auto moveDown2 = std::make_unique<dae::MoveDown>(go2.get());
	input.InputBinding(std::move(moveDown2), XINPUT_GAMEPAD_DPAD_DOWN, EInputType::hold, true);
	auto moveRight2 = std::make_unique<dae::MoveRight>(go2.get());
	input.InputBinding(std::move(moveRight2), XINPUT_GAMEPAD_DPAD_RIGHT, EInputType::hold, true);
	auto moveLeft2 = std::make_unique<dae::MoveLeft>(go2.get());
	input.InputBinding(std::move(moveLeft2), XINPUT_GAMEPAD_DPAD_LEFT, EInputType::hold, true);

	go2->SetLocalPosition(216, 200);
	scene.Add(std::move(go2));
	sceneInd = 3;

	//Create player 2 healt image object
	auto to2 = std::make_unique<dae::GameObject>();
	to2->AddComponent<TG::TextComponent>(to2.get(), "", font);
	to2->AddComponent<TG::HealthDisplay>(to2.get(), scene.GetObjectByIndex(3));
	to2->SetLocalPosition(5, 60);
	scene.Add(std::move(to2));
	sceneInd = 4;


	//Create FPS object
	auto fps = std::make_unique<dae::GameObject>();
	fps.get()->AddComponent<TG::TextComponent>(fps.get(), "0000.000FPS", font);
	fps.get()->AddComponent<TG::FPSComponent>(fps.get());
	fps->SetLocalPosition(200, 10);
	fps.get()->SetParent(scene.GetObjectByIndex(sceneInd), false);
	scene.Add(std::move(fps));
	sceneInd = 5;
}

int main(int, char*[]) 
{
	dae::Minigin engine("../Data/");
	engine.Run(load);

    return 0;
}
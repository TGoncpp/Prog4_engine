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
#include "TextComponent.h"
#include "FPSComponent.h"
#include "Rotator.h"
#include "MovementComponent.h"
#include <Xinput.h>




void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	auto& input = dae::InputManager::GetInstance();


	//Create Background object
	auto go = std::make_unique<dae::GameObject>();
	go->AddComponent<TG::RenderComponent>(go.get(), "background.tga");
	scene.Add(std::move(go));
	int sceneInd{ 0 };

	//Create Logo object
	go = std::make_unique<dae::GameObject>();
	go.get()->AddComponent<TG::RenderComponent>(go.get(), "logo.tga");	
	go->SetLocalPosition(216, 180);
	scene.Add(std::move(go));
	sceneInd = 1;

	//Create Center for rotation object
	auto cp = std::make_unique<dae::GameObject>();
	cp->SetLocalPosition(216, 180);
	scene.Add(std::move(cp));
	sceneInd = 2;

	//Create character object
	go = std::make_unique<dae::GameObject>();
	go.get()->AddComponent<TG::RenderComponent>(go.get(), "Qbert-P1.tga");	
	go.get()->AddComponent<TG::MovementComponent>(go.get(), 50.f);	
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
	sceneInd = 3;

	//Create character2 object
	auto go2 = std::make_unique<dae::GameObject>();
	go2.get()->AddComponent<TG::RenderComponent>(go2.get(), "Qbert-P2.tga");	
	go2.get()->AddComponent<TG::MovementComponent>(go2.get(), 100.f);	
	//inputMapping
	auto moveUp2 = std::make_unique<dae::MoveUp>(go2.get());
	input.InputBinding(std::move(moveUp2), XINPUT_GAMEPAD_DPAD_UP, EInputType::hold, true);
	auto moveDown2 = std::make_unique<dae::MoveDown>(go2.get());
	input.InputBinding(std::move(moveDown2), XINPUT_GAMEPAD_DPAD_DOWN, EInputType::hold, true);
	auto moveRight2 = std::make_unique<dae::MoveRight>(go2.get());
	input.InputBinding(std::move(moveRight2), XINPUT_GAMEPAD_DPAD_RIGHT, EInputType::hold, true);
	auto moveLeft2 = std::make_unique<dae::MoveLeft>(go2.get());
	input.InputBinding(std::move(moveLeft2), XINPUT_GAMEPAD_DPAD_LEFT, EInputType::hold, true);

	//go2.get()->SetParent(scene.GetObjectByIndex(sceneInd), true);
	go2->SetLocalPosition(216, 200);
	scene.Add(std::move(go2));
	sceneInd = 4;

	//Create Text object
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_unique<dae::GameObject>();
	to->AddComponent<TG::TextComponent>(to.get(), "Programming 4 Assignment", font);
	to->SetLocalPosition(80, 20);
	scene.Add(std::move(to));
	sceneInd = 5;

	//Create FPS object
	auto fps = std::make_unique<dae::GameObject>();
	fps.get()->AddComponent<TG::TextComponent>(fps.get(), "0000.000FPS", font);
	fps.get()->AddComponent<TG::FPSComponent>(fps.get());
	fps->SetLocalPosition(0, 80);
	fps.get()->SetParent(scene.GetObjectByIndex(sceneInd), false);
	scene.Add(std::move(fps));
	sceneInd = 6;
}

int main(int, char*[]) 
{
	dae::Minigin engine("../Data/");
	engine.Run(load);

    return 0;
}
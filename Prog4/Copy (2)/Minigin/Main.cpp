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
#include "TextObject.h"
#include "Scene.h"

#include "RenderComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "Rotator.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

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
	go.get()->AddComponent<TG::RotatorComponent>(go.get());	
	go.get()->SetParent(scene.GetObjectByIndex(sceneInd), false);
	scene.Add(std::move(go));
	sceneInd = 3;

	//Create character2 object
	auto go2 = std::make_unique<dae::GameObject>();
	go2.get()->AddComponent<TG::RenderComponent>(go2.get(), "Qbert-P2.tga");	
	go2.get()->AddComponent<TG::RotatorComponent>(go2.get());	
	go2.get()->SetParent(scene.GetObjectByIndex(sceneInd), false);
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
#include "SceneManager.h"
#include "Scene.h"

void TG::SceneManager::Update(float dt)
{
	for(auto& scene : m_scenes)
	{
		scene->Update(dt);
	}
}

void TG::SceneManager::FixedUpdate(float dt)
{
	for(auto& scene : m_scenes)
	{
		scene->FixedUpdate(dt);
	}
}

void TG::SceneManager::Render()
{
	for (const auto& scene : m_scenes)
	{
		scene->Render();
	}
}

TG::Scene& TG::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	//const auto& scene = std::make_unique<Scene>(name);
	m_scenes.push_back(scene);
	return *scene;
}

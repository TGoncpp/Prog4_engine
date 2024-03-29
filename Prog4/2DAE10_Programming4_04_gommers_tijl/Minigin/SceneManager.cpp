#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update(float dt)
{
	for(auto& scene : m_scenes)
	{
		scene->Update(dt);
	}
}

void dae::SceneManager::FixedUpdate(float dt)
{
	for(auto& scene : m_scenes)
	{
		scene->FixedUpdate(dt);
	}
}

void dae::SceneManager::Render()
{
	for (const auto& scene : m_scenes)
	{
		scene->Render();
	}
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	//const auto& scene = std::make_unique<Scene>(name);
	m_scenes.push_back(scene);
	return *scene;
}

#include "Scene.h"
#include "SceneManager.h"

#include <algorithm>
#include <iostream>

using namespace TG;

Scene::Scene(const std::string& name) : m_name(name) 
{
	
}

std::vector<int> TG::Scene::findGOwithName(const std::string& name)
{
	std::vector<int> playerIndexes;
	for (size_t index{}; index < m_objects.size(); ++index)
	{
		if (m_objects[index]->GetName() == name)
			playerIndexes.push_back(static_cast<int>(index));
	}
	if (playerIndexes.size()<= 0)
		throw std::runtime_error("gameObject with name is not found in scene");
	return playerIndexes;
}

Scene::~Scene() = default;

void Scene::Add(std::unique_ptr<GameObject> object)
{
	m_objects.emplace_back(std::move(object));
}

void Scene::Remove(std::unique_ptr<GameObject> object)
{
	m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

GameObject* TG::Scene::GetGO(size_t index) const
{
	if (index >= m_objects.size())
	{
		std::cout << "overflow index off game objects in scene\n";
		throw;
	}
	return m_objects[index].get();
}

void Scene::Update(float dt)
{
	for(auto& object : m_objects)
	{
		object->Update(dt);
	}
}

void Scene::FixedUpdate(float dt)
{
	for(auto& object : m_objects)
	{
		object->FixedUpdate(dt);
	}
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
}

void TG::Scene::ActivateInput(bool IsActive)
{
	std::vector<int> vPlayers = findGOwithName("Qbert");
	 for (size_t index{}; index < vPlayers.size(); ++index)
	 {
		 m_objects [vPlayers[index]] ->ActivateInput(IsActive);
	 }
}

void TG::Scene::ApplyGameMode(int activeGameMode)
{
	for (const auto& object : m_objects)
	{
		object->ApplyGameMode(activeGameMode);
	}
}


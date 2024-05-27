#include "Scene.h"
#include "SceneManager.h"

#include <algorithm>
#include <iostream>

using namespace TG;

Scene::Scene(const std::string& name) : m_name(name) 
{
	
}

size_t TG::Scene::findGOwithName(const std::string& name)
{
	for (size_t index{}; index < m_objects.size(); ++index)
	{
		if (m_objects[index]->GetName() == name)
			return index;
	}
	throw std::runtime_error("gameObject with name is not found in scene");
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

GameObject* TG::Scene::GetGO(int index) const
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
	size_t index = findGOwithName("Qbert");
	m_objects[index]->ActivateInput(IsActive);
}


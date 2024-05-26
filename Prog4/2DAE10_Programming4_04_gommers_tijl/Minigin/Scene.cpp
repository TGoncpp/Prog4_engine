#include "Scene.h"
#include "SceneManager.h"

#include <algorithm>

using namespace TG;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) 
{
	
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

void TG::Scene::Reset()
{
	for (const auto& object : m_objects)
	{
		object->Reset();
	}
}


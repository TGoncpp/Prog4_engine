#pragma once
#include "SceneManager.h"
#include "GameObject.h"

namespace TG
{
	class Scene final
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(std::unique_ptr<GameObject> object);
		void Remove(std::unique_ptr<GameObject> object);
		void RemoveAll();

		void Update(float dt);
		void FixedUpdate(float dt);
		void Render() const;

		GameObject* GetObjectByIndex(int index)const;

		~Scene();
		Scene(const Scene& other)            = delete;
		Scene(Scene&& other)                 = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other)      = delete;

	private: 
		explicit Scene(const std::string& name);

		std::string m_name;
		std::vector < std::unique_ptr<GameObject>> m_objects{};

		static unsigned int m_idCounter; 
	};

}

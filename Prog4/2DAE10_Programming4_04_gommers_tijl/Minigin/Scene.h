#pragma once
//#include "SceneManager.h"
#include "GameObject.h"

namespace TG
{
	class Scene final
	{
		//friend Scene& SceneManager::CreateScene(const EMenuState& name);
	public:
		void Add(std::unique_ptr<GameObject> object);
		void Remove(std::unique_ptr<GameObject> object);
		void RemoveAll();
		GameObject* GetGO(size_t index)const;

		void Update(float dt);
		void FixedUpdate(float dt);
		void Render() const;
		void ActivateInput(bool IsActive, int gameMode);
		void ApplyGameMode(int activeGameMode, int lvl = -1);

		~Scene();
		Scene(const Scene& other)            = delete;
		Scene(Scene&& other)                 = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other)      = delete;

		explicit Scene(const std::string& name);

	private: 

		std::string m_name;
		std::vector < std::unique_ptr<GameObject>> m_objects{};

		std::vector<int>  findGOwithName(const std::string& name);
	};

}

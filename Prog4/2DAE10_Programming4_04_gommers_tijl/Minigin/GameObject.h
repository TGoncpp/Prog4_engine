#pragma once
#include <memory>
#include <vector>
#include <algorithm>
#include "Transform.h"
#include "subject.h"

#include "BaseComponent.h"


namespace TG
{
	class RenderComponent;
	class Texture2D;
	class Font;

	class GameObject
	{
	public:
		//----------------------------------------
		//VIRTUAL FUNCTIONS
		virtual void Update(float dt);
		virtual void FixedUpdate(float dt);
		virtual void Render() const;

		//used by Command
		virtual void HandleInput(const glm::vec2&) {};

		//used by scene for (de)activating game input 
		virtual void ActivateInput(bool ) {};
		virtual void ApplyGameMode(int, int = 1 ) {};

		//for (de)Activating input
		Subject<bool> OnActivateInput;

		//----------------------------------------
		//TRANSFORM FUNCTIONS
		void SetLocalPosition(float x, float y);
		void SetLocalPosition(const glm::vec2& pos);
		void SetWorldPosition(float x, float y);
		void SetWorldPosition(const glm::vec3& pos);
		glm::vec3 GetLocalPosition()const { return m_LocalTransform.GetPosition(); };
		glm::vec3 GetWorldPosition();

		//----------------------------------------
		//COMPONENT FUNCTIONS
		template <typename T, typename... Args>
		T* AddComponent(Args&&... args)
		{
			m_vComponentUPtrs.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
			return static_cast<T*>(m_vComponentUPtrs.back().get());
		}
		template <typename T>
		void RemoveComponent()
		{
			static_assert(std::is_base_of<TG::BaseComponent, T>::value, "T must be a subclass of BaseComponent");
			auto it = std::remove_if(m_vComponentUPtrs.begin(), m_vComponentUPtrs.end(), [](const std::unique_ptr<TG::BaseComponent>& pComponent)
				{
					return dynamic_cast<T*>(pComponent.get()) != nullptr;
				});
			if (it == m_vComponentUPtrs.end())
				throw;
			m_vComponentUPtrs.erase(it, m_vComponentUPtrs.end());
		}
		template<typename T>
		T* GetComponent() const
		{
			static_assert(std::is_base_of<TG::BaseComponent, T>::value, "T must be a subclass of BaseComponent");
			auto it = std::find_if(m_vComponentUPtrs.begin(), m_vComponentUPtrs.end(), [](const std::unique_ptr<TG::BaseComponent>& pComponent)
				{
					return dynamic_cast<T*>(pComponent.get()) != nullptr;
				});

			assert(it != m_vComponentUPtrs.end() && "Component to get not found");

			return static_cast<T*>((*it).get());
		}		
		template<typename T>
		std::vector<T*> GetAllComponent() const
		{
			std::vector<T*>vResult;
			static_assert(std::is_base_of<TG::BaseComponent, T>::value, "T must be a subclass of BaseComponent");
			std::for_each(m_vComponentUPtrs.begin(), m_vComponentUPtrs.end(), [&vResult](const std::unique_ptr<TG::BaseComponent>& pComponent)
			{
				if (dynamic_cast<T*>(pComponent.get()) != nullptr)
					vResult.push_back(static_cast<T*>(pComponent.get()));
				 
			});

			return vResult;
		}		
		template <typename T>
		bool CheckComponent()const
		{
			auto it = std::find_if(m_vComponentUPtrs.begin(), m_vComponentUPtrs.end(), [](const std::unique_ptr<TG::BaseComponent>& component)
				{return dynamic_cast<T*>(component.get()) != nullptr; });
			return (it != m_vComponentUPtrs.end());

		};

		//----------------------------------------
		//HIERARCHICAL FUNCTIONS
		void SetParent(GameObject* parent, bool keepWorldPosition);
		GameObject* GetParent() { return m_parentPtr; };
		GameObject* GetChildAtIndex(size_t index) { return m_vChildPtrs[index]; };
		size_t GetNumOfChilds() { return m_vChildPtrs.size(); };
		void SetPositionDirty() { m_IsPositionDirty = true; };
		bool IsChild(const GameObject* otherObj)const;

		//----------------------------------------
		//RULE OFF 5 FUNCTIONS
		GameObject(const std::string& name = "")
			:m_Name{ name } {}
		virtual ~GameObject()                          = default;
		GameObject(const GameObject& other)            = delete;
		GameObject(GameObject&& other)                 = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other)      = delete;

		std::string GetName()const {return m_Name ; };
		void SetName(const std::string& name) {m_Name = name; };

	protected:
		std::string m_Name{ "default" };

	private:
		Transform m_LocalTransform{};
		Transform m_WorldTransform{};
		std::vector<std::unique_ptr<TG::BaseComponent>> m_vComponentUPtrs{};
		std::vector<GameObject*> m_vChildPtrs{};
		GameObject* m_parentPtr{};
		bool m_IsPositionDirty{ false };
		void UpdateWorldPosition();

		void AddChild(GameObject* child);
		void RemoveChild(GameObject* child);
	};
}

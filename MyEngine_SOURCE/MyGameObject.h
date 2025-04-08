#pragma once
#include "CommonInclude.h"
#include "MyComponent.h"

namespace Source
{
	class GameObject
	{
	public:
		enum class GameObjectState
		{
			Active,
			Inactive,
			Destroy
		};

		GameObject();
		~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);

		template <typename T>
		T* AddComponent()
		{
			T* component = new T();
			component->Initialize();

			component->SetOwner(this);
			_components[(UINT)component->GetType()] = component;
			//_components.push_back(component);

			return component;
		}

		template <typename T>
		T* GetComponent()
		{
			T* componentResult = nullptr;
			for (Component* comp : _components)
			{
				componentResult = dynamic_cast<T*>(comp);
				if (componentResult != nullptr)
				{
					break;
				}
			}

			return componentResult;
		}

		void SetActive(bool isActive)
		{
			if (isActive)
			{
				_state = GameObjectState::Active;
			}
			else
			{
				_state = GameObjectState::Inactive;
			}
		}
		GameObjectState GetActive() { return _state; }

		void SetDestroy() { _state = GameObjectState::Destroy; }

	private:
		GameObjectState _state;
		std::vector<Component*> _components;
	};
}



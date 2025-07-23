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

		GameObjectState GetActive() const { return _state; }
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
		bool IsActive() const { return _state == GameObjectState::Active; }

		LayerType GetLayerType() const { return _layerType; }
		void SetLayerType(LayerType layerType) { _layerType = layerType; }

		void SetDestroy() { _state = GameObjectState::Destroy; }

	private:
		GameObjectState _state;
		std::vector<Component*> _components;
		LayerType _layerType;
	};
}



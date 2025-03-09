#pragma once
#include "CommonInclude.h"
#include "MyComponent.h"

namespace Source
{
	class GameObject
	{
	public:
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

	private:
		std::vector<Component*> _components;
	};
}



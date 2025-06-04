#include "MyGameObject.h"
#include "MyInput.h"
#include "MyTime.h"
#include "MyTransform.h"

namespace Source
{
	GameObject::GameObject() :
		_state(GameObjectState::Active),
		_components(),
		_layerType(Enums::LayerType::None)
	{
		_components.resize((UINT)Enums::ComponentType::END);
		AddComponent<Transform>();
	}

	GameObject::~GameObject()
	{
		for (Component* comp : _components)
		{
			if (comp != nullptr)
			{
				delete comp;
				comp = nullptr;
			}
		}
		_components.clear();
	}
	
	void GameObject::Initialize()
	{
		for (Component* comp : _components)
		{
			if (comp == nullptr)
			{
				continue;
			}

			comp->Initialize();
		}
	}

	void GameObject::Update()
	{
		for (Component* comp : _components)
		{
			if (comp == nullptr)
			{
				continue;
			}

			comp->Update();
		}
	}

	void GameObject::LateUpdate()
	{
		for (Component* comp : _components)
		{
			if (comp == nullptr)
			{
				continue;
			}

			comp->LateUpdate();
		}
	}

	void GameObject::Render(HDC hdc)
	{
		for (Component* comp : _components)
		{
			if (comp == nullptr)
			{
				continue;
			}

			comp->Render(hdc);
		}
	}
}


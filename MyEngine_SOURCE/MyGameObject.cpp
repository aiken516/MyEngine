#include "MyGameObject.h"
#include "MyInput.h"
#include "MyTime.h"
#include "MyTransform.h"

namespace Source
{
	GameObject::GameObject()
	{
		AddComponent<Transform>();
	}

	GameObject::~GameObject()
	{
	}
	
	void GameObject::Initialize()
	{
		for (Component* comp : _components)
		{
			comp->Initialize();
		}
	}

	void GameObject::Update()
	{
		for (Component* comp : _components)
		{
			comp->Update();
		}
	}

	void GameObject::LateUpdate()
	{
		for (Component* comp : _components)
		{
			comp->LateUpdate();
		}
	}

	void GameObject::Render(HDC hdc)
	{
		for (Component* comp : _components)
		{
			comp->Render(hdc);
		}
	}
}


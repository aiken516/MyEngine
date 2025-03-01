#include "MyGameObject.h"
#include "MyInput.h"
#include "MyTime.h"

namespace Source
{
	GameObject::GameObject()
	{
	}

	GameObject::~GameObject()
	{
	}
	
	void GameObject::Initialize()
	{
		for (Component* comp : components_)
		{
			comp->Initialize();
		}
	}

	void GameObject::Update()
	{
		for (Component* comp : components_)
		{
			comp->Update();
		}
	}

	void GameObject::LateUpdate()
	{
		for (Component* comp : components_)
		{
			comp->LateUpdate();
		}
	}

	void GameObject::Render(HDC hdc)
	{
		for (Component* comp : components_)
		{
			comp->Render(hdc);
		}
	}
}


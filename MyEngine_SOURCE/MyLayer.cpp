#include "MyLayer.h"

namespace Source
{
	Layer::Layer() :
		gameObjects_{}
	{
	}

	Layer::~Layer()
	{
	}

	void Layer::Initialize()
	{
		for (GameObject* go : gameObjects_)
		{
			if (go == nullptr)
			{
				continue;
			}

			go->Initialize();
		}
	}
	
	void Layer::Update()
	{
		for (GameObject* go : gameObjects_)
		{
			if (go == nullptr)
			{
				continue;
			}

			go->Update();
		}
	}
	
	void Layer::LateUpdate()
	{
		for (GameObject* go : gameObjects_)
		{
			if (go == nullptr)
			{
				continue;
			}

			go->LateUpdate();
		}
	}

	void Layer::Render(HDC hdc)
	{
		for (GameObject* go : gameObjects_)
		{
			if (go == nullptr)
			{
				continue;
			}

			go->Render(hdc);
		}
	}

	void Layer::AddGameObject(GameObject* gameObject)
	{
		if (gameObject == nullptr)
		{
			return;
		}

		gameObjects_.push_back(gameObject);
	}
}
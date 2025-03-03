#include "MyLayer.h"

namespace Source
{
	Layer::Layer() :
		_gameObjects{}
	{
	}

	Layer::~Layer()
	{
	}

	void Layer::Initialize()
	{
		for (GameObject* go : _gameObjects)
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
		for (GameObject* go : _gameObjects)
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
		for (GameObject* go : _gameObjects)
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
		for (GameObject* go : _gameObjects)
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

		_gameObjects.push_back(gameObject);
	}
}
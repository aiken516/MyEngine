#include "MyLayer.h"

namespace Source
{
	Layer::Layer() :
		_gameObjects{}
	{
	}

	Layer::~Layer()
	{
		for (GameObject* go : _gameObjects)
		{
			if (go != nullptr)
			{
				delete go;
				go = nullptr;
			}
		}
		_gameObjects.clear();
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

			GameObject::GameObjectState state = go->GetActive();
			if (state == GameObject::GameObjectState::Inactive ||
				state == GameObject::GameObjectState::Destroy)
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

			GameObject::GameObjectState state = go->GetActive();
			if (state == GameObject::GameObjectState::Inactive ||
				state == GameObject::GameObjectState::Destroy)
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

			GameObject::GameObjectState state = go->GetActive();
			if (state == GameObject::GameObjectState::Inactive ||
				state == GameObject::GameObjectState::Destroy)
			{
				continue;
			}

			go->Render(hdc);
		}
	}

	void Layer::Destroy()
	{
		for (GameObjectIter iter = _gameObjects.begin(); iter != _gameObjects.end();)
		{
			GameObject::GameObjectState state = (*iter)->GetActive();
			if (state == GameObject::GameObjectState::Destroy)
			{
				GameObject* destroyObject = (*iter);

				iter = _gameObjects.erase(iter);

				delete destroyObject;
				destroyObject = nullptr;

				continue;
			}

			iter++;
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

	void Layer::RemoveGameObject(GameObject* gameObject)
	{
		for (auto deleteObject = _gameObjects.begin(); deleteObject != _gameObjects.end(); deleteObject++)
		{
			if (*deleteObject == gameObject)
			{
				_gameObjects.erase(deleteObject);
				break;
			}
		}
	}
}
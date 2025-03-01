#include "MyScene.h"

namespace Source
{
	Scene::Scene() : 
		gameObjects_{}
	{
	}
	Scene::~Scene()
	{
	}

	void Scene::Initialize()
	{
	}

	void Scene::Update()
	{
		for (GameObject* go : gameObjects_)
		{
			go->Update();
		}
	}

	void Scene::LateUpdate()
	{
		for (GameObject* go : gameObjects_)
		{
			go->LateUpdate();
		}
	}

	void Scene::Render(HDC hdc)
	{
		for (GameObject* go : gameObjects_)
		{
			go->Render(hdc);
		}
	}
	
	void Scene::AddGameObject(GameObject* gameObject)
	{
		gameObjects_.push_back(gameObject);
	}
}
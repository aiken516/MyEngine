#include "MyScene.h"
#include "MyCollisionManager.h"

namespace Source
{
	Scene::Scene() : 
		_sceneLayers{}
	{
		CreateLayers();
	}

	Scene::~Scene()
	{
		for (Layer* layer : _sceneLayers)
		{
			if (layer != nullptr)
			{
				delete layer;
				layer = nullptr;
			}
		}
		_sceneLayers.clear();
	}

	void Scene::Initialize()
	{
		for (Layer* layer : _sceneLayers)
		{
			if (layer == nullptr)
			{
				continue;
			}

			layer->Initialize();
		}
	}

	void Scene::Update()
	{
		for (Layer* layer : _sceneLayers)
		{
			if (layer == nullptr)
			{
				continue;
			}

			layer->Update();
		}
	}

	void Scene::LateUpdate()
	{
		for (Layer* layer : _sceneLayers)
		{
			if (layer == nullptr)
			{
				continue;
			}

			layer->LateUpdate();
		}
	}

	void Scene::Render()
	{
		for (Layer* layer : _sceneLayers)
		{
			if (layer == nullptr)
			{
				continue;
			}

			layer->Render();
		}
	}

	void Scene::Destroy()
	{
		for (Layer* layer : _sceneLayers)
		{
			if (layer == nullptr)
			{
				continue;
			}
			layer->Destroy();
		}
	}

	void Scene::OnEnter()
	{
	
	}

	void Scene::OnExit()
	{
		CollisionManager::Clear();
	}

	void Scene::CreateLayers()
	{
		_sceneLayers.resize((UINT)Enums::LayerType::MAX);
		for (size_t i = 0; i < (UINT)Enums::LayerType::MAX; i++)
		{
			_sceneLayers[i] = new Layer();
		}
	}

	void Scene::RemoveGameObject(GameObject* gameObject)
	{
		LayerType layerType = gameObject->GetLayerType();
		_sceneLayers[(UINT)layerType]->RemoveGameObject(gameObject);
	}

	void Scene::AddGameObject(GameObject* gameObject, const Enums::LayerType layerType)
	{
		_sceneLayers[(UINT)layerType]->AddGameObject(gameObject);
	}
}
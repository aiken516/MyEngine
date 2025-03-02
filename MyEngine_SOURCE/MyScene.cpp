#include "MyScene.h"

namespace Source
{
	Scene::Scene() : 
		layers_{}
	{
		CreateLayers();
	}
	Scene::~Scene()
	{
	}

	void Scene::Initialize()
	{
		for (Layer* layer : layers_)
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
		for (Layer* layer : layers_)
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
		for (Layer* layer : layers_)
		{
			if (layer == nullptr)
			{
				continue;
			}

			layer->LateUpdate();
		}
	}

	void Scene::Render(HDC hdc)
	{
		for (Layer* layer : layers_)
		{
			if (layer == nullptr)
			{
				continue;
			}

			layer->Render(hdc);
		}
	}

	void Scene::OnEnter()
	{
	
	}

	void Scene::OnExit()
	{
	
	}

	void Scene::CreateLayers()
	{
		layers_.resize((UINT)LayerType::MAX);
		for (size_t i = 0; i < (UINT)LayerType::MAX; i++)
		{
			layers_[i] = new Layer();
		}
	}

	void Scene::AddGameObject(GameObject* gameObject, LayerType layerType)
	{
		layers_[(UINT)layerType]->AddGameObject(gameObject);
	}
}
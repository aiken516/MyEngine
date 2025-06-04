#pragma once
#include "MyComponent.h"
#include "MyLayer.h"
#include "MyGameObject.h"
#include "MySceneManager.h"
#include "MyScene.h"
#include "MyTransform.h"

namespace Source::Object
{
	template <typename T>
	static T* Instantiate(Enums::LayerType type)
	{
		T* gameObject = new T();
		Scene* activeScene = SceneManager::GetActiveScene();
		Layer* layer = activeScene->GetLayer(type);
		layer->AddGameObject(gameObject);

		gameObject->SetLayerType(type);

		return gameObject;
	}

	template <typename T>
	static T* Instantiate(Enums::LayerType type, Vector2 position)
	{
		T* gameObject = Instantiate<T>(type);

		gameObject->GetComponent<Transform>()->SetPosition(position);

		return gameObject;
	}

	static void Destroy(GameObject* gameObject)
	{
		gameObject->SetDestroy();
	}

	static void DontDestroyOnLoad(GameObject* gameObject)
	{
		//오브젝트를 현재 씬에서 제거
		Scene* activeScene = SceneManager::GetActiveScene();
		activeScene->RemoveGameObject(gameObject);

		Scene* dontDestroyOnLoad = SceneManager::GetDontDestroyOnLoad();
		dontDestroyOnLoad->AddGameObject(gameObject, gameObject->GetLayerType());
	}
}
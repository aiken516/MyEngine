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
}